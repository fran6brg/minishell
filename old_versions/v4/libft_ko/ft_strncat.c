/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:24:36 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:54 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t j;

	i = -1;
	j = -1;
	while (dest[++i] != '\0')
		;
	while (src[++j] != '\0' && j < n)
		dest[j + i] = src[j];
	dest[j + i] = '\0';
	return (dest);
}
