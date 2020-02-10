/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:01:16 by fberger           #+#    #+#             */
/*   Updated: 2020/02/10 19:22:43 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** malloc 2D str array
*/

char	*ft_malloc_str(int nb_str)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char *) * (nb_str + 1))))
		return (NULL);
	i = -1;
	while (++i < nb_str)
		str[i] = 0;
	str[i] = '\0';
	return (str);
}
