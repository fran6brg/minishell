/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 06:04:39 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 03:40:03 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_ter(char const *s1, char const *s2, char const *s3)
{
	size_t	s1len;
	size_t	s2len;
	size_t	s3len;
	char	*join;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3len = ft_strlen(s3);
	if (!(join = malloc(sizeof(char) * (s1len + s2len + s3len + 1))))
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + s1len, s2);
	ft_strcpy(join + s1len + s2len, s3);
	return (join);
}
