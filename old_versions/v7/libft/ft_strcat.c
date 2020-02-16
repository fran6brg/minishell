/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:46:54 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:34 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (dest[++i] != '\0')
		;
	while (src[++j] != '\0')
		dest[j + i] = src[j];
	dest[j + i] = '\0';
	return (dest);
}
