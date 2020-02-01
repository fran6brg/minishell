/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:26:16 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 03:45:23 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** set_fd_if_redirection()
*/

void	set_fd_if_redirection(char **cmd_tab, int *fd)
{
	*fd = get_fd(cmd_tab);
	if (*fd != -1 && right_redirected_cmd(cmd_tab))
		dup2(*fd, STDOUT_FILENO);
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
		dup2(*fd, STDIN_FILENO);
}

/*
** restore_std_if_redirection()
**
** https://stackoverflow.com/questions/9084099/re-opening-stdout-and-stdin-file-descriptors-after-closing-them
*/

void	restore_std_if_redirection(char **cmd_tab, int *fd)
{
	if (*fd != -1 && right_redirected_cmd(cmd_tab))
	{
		close((*fd && *fd != -1) ? *fd : -1); // close fd, as usual
		dup2(STDIN_FILENO, 1); // restore stdin
	}
	else if (*fd != -1 && left_redirected_cmd(cmd_tab))
	{
		close((*fd && *fd != -1) ? *fd : -1); // close fd, as usual
		dup2(STDOUT_FILENO, 0); // restore stdout
	}
}
