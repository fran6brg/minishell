/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 04:37:58 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:52 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*new_s;

	if (s && f)
	{
		i = -1;
		while (s[++i])
			;
		if ((new_s = malloc(sizeof(char) * i + 1)) == NULL)
			return (NULL);
		new_s[i] = '\0';
		while (--i >= 0)
			new_s[i] = f(s[i]);
		return (new_s);
	}
	return (NULL);
}
