/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequci.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:50:15 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 21:51:25 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** str equal case insensitive
*/

int		ft_strequci(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && ft_letterequci(s1[i], s2[i]))
			i++;
		return (ft_letterequci(s1[i], s2[i]) ? 1 : 0);
	}
	return (0);
}
