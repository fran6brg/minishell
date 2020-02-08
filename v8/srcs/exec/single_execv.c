/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_execv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:55:13 by fberger           #+#    #+#             */
/*   Updated: 2020/02/08 14:06:19 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** waitpid_and_free_args
**
** nb : il faut free apres la fin du pid
*/

void	waitpid_and_free_args(pid_t child, int tube[2],
		int right_side, char **args)
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
	char	**args;
	pid_t	child;
	int		fd;
	int		ret;

	if (DEBUG)
		ft_print_str_tab(cmd_tab, "run_single_execv > cmd_tab"); // pour debug
	if ((args = format_args(cmd_tab, 1)))
	{
		if (DEBUG)
			ft_print_str_tab(args, "args"); // pour debug
		if ((child = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (child == 0)
		{
			set_fd_for_single_cmd(cmd_tab, &fd);
			ret = execv(args[0], args);
			restore_std_for_single_cmd(cmd_tab, &fd);
			exit(ret);
		}
		else
			waitpid_and_free_args(child, NULL, 0, args);
	}
}
