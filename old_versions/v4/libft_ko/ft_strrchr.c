/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:06:38 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 01:55:03 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	if (!s || !c)
		return (NULL);
	ptr = (char *)s;
	i = -1;
	while (ptr[++i])
		;
	while (i >= 0)
	{
		if (ptr[i] == (char)c)
			return ((ptr + i));
		i--;
	}
	return (NULL);
}
