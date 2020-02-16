/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:37 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 21:21:24 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if (!(sub = malloc(sizeof(char) * len + 1)))
			return ((char *)NULL);
		j = -1;
		while (++j < len)
			sub[j] = s[i + j];
		sub[len] = '\0';
		return (sub);
	}
	return ((char *)NULL);
}
