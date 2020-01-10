/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:22:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 20:23:21 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** free cmds
*/

void	free_cmds(char *cmd, char **cmd_tab)
{
	int i;

    i = -1;
    while (cmd_tab[++i])
    	ft_strdel(&cmd_tab[i]);
    free(cmd_tab);		
    ft_strdel(&cmd);		
}

/*
** free env list
*/

void   free_env(t_env *elem)
{
    t_env *tmp;

	while (elem)
	{
		tmp = elem->next;
		ft_strdel(&elem->name);
		ft_strdel(&elem->value);
		elem = tmp;
	}
}
