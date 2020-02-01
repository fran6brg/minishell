/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 01:24:43 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*sub;

	if (!s || ft_strlen(s) < start)
	{
		if (!(sub = malloc(sizeof(char) * 1)))
			return (0);
		*sub = '\0';
		return (sub);
	}
	i = -1;
	while (s[++i] && i != start)
		;
	if (i == start)
	{
		if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		j = 0;
		while (s[i + j] && j < len)
		{
			sub[j] = s[i + j];
			j++;
		}
		sub[len] = '\0';
		return (sub);
	}
	return (NULL);
}
