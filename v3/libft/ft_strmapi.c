/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 04:58:12 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:53 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*new_s;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	new_s[i] = '\0';
	i = -1;
	while (s[++i])
		new_s[i] = f(i, s[i]);
	return (new_s);
}
