/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_execv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:55:13 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 04:01:54 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** waitpid_and_free_args
**
** nb : il faut free apres la fin du pid
*/

void	waitpid_and_free_args(pid_t child, int tube[2], int right_side, char **args)
{
	int	status;
	
	if (right_side)
	{
		close(tube[WRITE]);
		close(tube[READ]);
	}
	status = 0;
	waitpid(child, &status, 0);
	ft_free_str_tab(args);
}

/*
** run_single_execv()
**
** if (child == -1) : erreur
** else if (child == 0) : process fils
** else : process parent
*/

void	run_single_execv(char **cmd_tab)
{
	char	**formated_args;
	pid_t   child;
	int		fd;
	int		ret;

	if ((formated_args = get_first_args(cmd_tab)))
	{
		if (DEBUG)
			ft_print_str_tab(formated_args, "formated_args inside run_single_execv");
		if ((child = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (child == 0)
		{
			set_fd_if_redirection(cmd_tab, &fd);
			ret = execv(formated_args[0], formated_args);
			restore_std_if_redirection(cmd_tab, &fd);
			exit(ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
		}
		else
			waitpid_and_free_args(child, NULL, 0, formated_args);
	}
}
