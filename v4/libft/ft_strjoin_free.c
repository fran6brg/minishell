/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 06:04:39 by fberger           #+#    #+#             */
/*   Updated: 2020/01/11 07:01:01 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	if (!(join = malloc(sizeof(char) * (s1len + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + s1len, s2);
	/*
	** trouver pq free ici produit un double free
	*/
	return (join);
}
