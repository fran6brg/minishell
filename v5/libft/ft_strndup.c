/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:55:46 by fberger           #+#    #+#             */
/*   Updated: 2019/11/14 19:47:36 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char		*dup;
	size_t		i;

	if (!(dup = malloc(sizeof(char) * (ft_min(ft_strlen(src), n) + 1))))
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
