/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_char_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:59:22 by fberger           #+#    #+#             */
/*   Updated: 2020/01/13 12:22:59 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_next_char_pos(const char *s, char *set)
{
	size_t	i;
	int		j;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (set[++j])
			if (s[i] == set[j])
				return (i);
	}
	return (i);
}
