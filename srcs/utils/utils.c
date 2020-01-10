/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 20:32:02 by fberger          ###   ########.fr       */
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
    while (s[++i])
    {
        ft_printf("split[%d] = -%s-\n", i, s[i]);
    }
}

/*
** count_arg
*/

int    nb_arg(char **s)
{
    int i;

    i = 0;
    while (s[++i])
		;
	return (i);
}
