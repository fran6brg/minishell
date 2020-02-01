/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 06:04:39 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 21:28:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*duplicate_ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = -1;
	while (src[++i] && (dest[i] = src[i]))
		;
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	if (!(join = malloc(sizeof(char) * (s1len + ft_strlen(s2) + 1))))
		return (NULL);
	duplicate_ft_strcpy(join, s1);
	duplicate_ft_strcpy(join + s1len, s2);
	return (join);
}
