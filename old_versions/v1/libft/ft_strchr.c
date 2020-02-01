/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:39:00 by fberger           #+#    #+#             */
/*   Updated: 2020/01/13 11:59:17 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*sptr;
	int		i;

	sptr = (char *)s;
	i = -1;
	while (sptr[++i])
	{
		if (sptr[i] == (char)c)
			return (sptr + i);
	}
	if ((char)c == '\0')
		return (sptr + i);
	return ((char *)0);
}
