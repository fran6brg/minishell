/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:22:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 07:18:50 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** free cmds
*/

void	free_cmds(char *line, char **cmds)
{
	if (cmds)
		ft_free_str_tab(cmds);
    ft_strdel(&line);
}

/*
** free env list
*/

void   free_env()
{
    t_env *tmp;

	while (g_env)
	{
		tmp = g_env->next;
		ft_strdel(&g_env->name);
		ft_strdel(&g_env->value);
		if (g_env)
			free(g_env);
		g_env = tmp;
	}
}

/*
** free_and_exit
*/

void	free_and_exit(int exit_value, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	free_env();
	exit(exit_value);
}