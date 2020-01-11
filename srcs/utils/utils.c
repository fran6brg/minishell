/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/11 06:16:43 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** print str split
*/

void    print_str_split(char **s)
{
    int i;

    i = -1;
    ft_printf("***********\n");
    while (s[++i])
        ft_printf("split[%d] = -%s-\n", i, s[i]);
    ft_printf("***********\n");
}

/*
** count_arg
*/

int    count_arg(char **s)
{
    int i;

    i = 0;
    while (s[++i])
		;
	return (i);
}
