/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 03:14:25 by fberger          ###   ########.fr       */
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