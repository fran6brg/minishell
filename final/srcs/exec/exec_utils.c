/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:04:17 by fberger           #+#    #+#             */
/*   Updated: 2020/02/05 12:19:34 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** next_pipe_pos_or_len();
*/

int		next_pipe_pos_or_len(char **cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i][0] == '|')
			return (i);
		i++;
	}
	return (i);
}

/*
** count_pipe();
*/

int		count_pipe(char **cmd_tab)
{
	int	i;
	int	nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i][0] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}

/*
** exit_process(int pdes[2], pid_t child);
*/

int		exit_process(int pdes[2])
{
	close(pdes[READ]);
	close(pdes[WRITE]);
	exit(EXIT_FAILURE);
}
