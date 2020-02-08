/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_str_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:01:16 by fberger           #+#    #+#             */
/*   Updated: 2020/02/08 13:05:49 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** malloc 2D str array
*/

char	**ft_malloc_str_tab(int nb_str)
{
	char	**strs;
	int		i;

	if (!(strs = malloc(sizeof(char *) * (nb_str + 1))))
		return (NULL);
	i = -1;
	while (++i < nb_str)
		strs[i] = (char *)NULL;
	strs[i] = NULL;
	return (strs);
}
