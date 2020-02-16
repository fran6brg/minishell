/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:26:16 by fberger           #+#    #+#             */
/*   Updated: 2020/02/05 13:42:32 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** set_fd_for_single_cmd()
*/

void	set_fd_for_single_cmd(char **cmd_tab, int *fd)
{
	*fd = get_fd(cmd_tab);
	if (*fd != -1 && right_redirected_cmd(cmd_tab))
		dup2(*fd, STDOUT_FILENO);
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
		dup2(*fd, STDIN_FILENO);
}

/*
** restore_std_for_single_cmd()
**
** close fd, as usual
** restore stdin or stdout
** https://stackoverflow.com/questions/9084099
*/

void	restore_std_for_single_cmd(char **cmd_tab, int *fd)
{
	if (*fd != -1 && right_redirected_cmd(cmd_tab))
	{
		close((*fd && *fd >= 3) ? *fd : -1);
		dup2(STDIN_FILENO, 1);
	}
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
	{
		close((*fd && *fd >= 3) ? *fd : -1);
		dup2(STDOUT_FILENO, 0);
	}
}

/*
** set_fd_for_left_pipped_cmd()
*/

void	set_fd_for_left_pipped_cmd(char **cmd_tab, int tube[2], int *fd)
{
	if ((*fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab))
		dup2(*fd, STDOUT_FILENO);
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
		dup2(*fd, STDIN_FILENO);
	else
		dup2(tube[WRITE], STDOUT_FILENO);
}

/*
** set_fd_for_right_pipped_cmd()
*/

void	set_fd_for_right_pipped_cmd(char **cmd_tab,
int tube[2], int *fd)
{
	if ((*fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab))
	{
		close(tube[WRITE]);
		dup2(tube[READ], STDIN_FILENO);
		dup2(*fd, STDOUT_FILENO);
	}
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
	{
		close(tube[WRITE]);
		dup2(*fd, STDIN_FILENO);
	}
	else
	{
		close(tube[WRITE]);
		dup2(tube[READ], STDIN_FILENO);
	}
}

/*
** restore_std_for_left_pipped_cmd()
**
** close fd, as usual
** restore stdin or stdout
** https://stackoverflow.com/questions/9084099
*/

void	restore_std_for_pipped_cmd(int tube[2],
int *fd, char **args)
{
	close((*fd && *fd >= 3) ? *fd : -1);
	if (tube || args)
		;
}
