/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:26:16 by fberger           #+#    #+#             */
/*   Updated: 2020/02/04 07:15:26 by fberger          ###   ########.fr       */
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
	// close(tube[READ]);
	if ((*fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab))
	{
		dup2(*fd, STDOUT_FILENO);
	}
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
	{
		dup2(*fd, STDIN_FILENO);
	}
	else
	{
		dup2(tube[WRITE], STDOUT_FILENO);
	}
}

/*
** restore_std_for_left_pipped_cmd()
**
** close fd, as usual
** restore stdin or stdout
** https://stackoverflow.com/questions/9084099
*/

void	restore_std_for_left_pipped_cmd(int tube[2], int *fd, char **args)
{
	if (DEBUG)
		ft_print_str_tab(args, "restore_std_for_left_pipped_cmd"); // pour debug
	close((*fd && *fd >= 3) ? *fd : -1);
	if (tube || args)
		;
}

/*
** set_fd_for_right_pipped_cmd()
*/

void	set_fd_for_right_pipped_cmd(char **cmd_tab, int tube[2], int *fd)
{
	// if (DEBUG)
	// 	ft_print_str_tab(args, "set_fd_for_right_pipped_cmd"); // pour debug
	if ((*fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab))
	{
		close(tube[WRITE]); // ok: on close le write car il sert a rien ici
		dup2(tube[READ], STDIN_FILENO); // ok: avec dup2 le stdin de right est le stdout de left child
		dup2(*fd, STDOUT_FILENO); // ici il y a un pb ... ? pourtant ecrire sur stdout revient desormais a ecrire sur fd
	}
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
	{
		close(tube[WRITE]); // ok: on close le write car il sert a rien ici
		dup2(*fd, STDIN_FILENO); // ok
	}
	else
	{
		close(tube[WRITE]); // ok: on close le write car il sert a rien ici
		dup2(tube[READ], STDIN_FILENO); // ok
	}
}

/*
** restore_std_for_right_pipped_cmd()
**
** close fd, as usual
** restore stdin or stdout
** https://stackoverflow.com/questions/9084099
*/

void	restore_std_for_right_pipped_cmd(int tube[2], int *fd, char **args)
{
	if (DEBUG)
		ft_print_str_tab(args, "restore_std_for_right_pipped_cmd"); // pour debug
	close((*fd && *fd >= 3) ? *fd : -1);
	if (tube || args)
		;
}
