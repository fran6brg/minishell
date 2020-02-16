/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:32:52 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:42:22 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *m, const char *a)
{
	int i;
	int j;

	i = -1;
	if (ft_strlen(a) == 0)
		return ((char *)m);
	while (m[++i])
	{
		j = 0;
		while (a[j] == m[i + j] && m[i + j])
			j++;
		if (a[j] == '\0')
			return (((char *)m) + i);
	}
	return (0);
}
