/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:22:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/18 22:54:16 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** global var for put_promt()
*/

t_env	*g_env;

/*
** free 2D str array
*/

void	free_str_tab(char **str_tab)
{
	int i;

    i = -1;
    while (str_tab && str_tab[++i])
    	ft_strdel(&str_tab[i]);
    if (str_tab)
	{
		free(str_tab);
		str_tab = NULL;
	}
}

/*
** free cmds
*/

void	free_cmds(char *line, char **cmds)
{
    free_str_tab(cmds);		
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