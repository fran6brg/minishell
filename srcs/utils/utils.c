/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 03:43:26 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** print env list
*/

void	print_env(t_env *env_list)
{
	t_env	*var;
	int		i;

	var = env_list;
	i = 0;
    printf("hello\n");
	while (var)
	{
        printf("hello\n");
		printf("----------------\n%02d->[%s] = [%s]\n", ++i, var->name, var->value);
		var = var->next;
	}
}

/*
** print str split
*/

void    print_str_split(char **s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        ft_printf("split[%d] = -%s-\n", i, s[i]);
    }
}

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
