/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_ws.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:36 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 19:03:52 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_ws(char c)
{
	return (c == 32 || c == 9 || c == 10);
}

static int	is_last_char(char const *str)
{
	int		i;

	i = 0;
	while (str[i] && is_ws(str[i]))
		i++;
	return ((str[i] == '\0') ? 1 : 0);
}

char		*ft_strtrim_ws(char const *s1)
{
	int		i;
	int		start;
	int		len;
	char	*new_s;

	if (!s1)
		return ((char *)NULL);
	i = -1;
	while (s1[++i] && is_ws(s1[i]))
		;
	start = i;
	i = 1;
	while (is_last_char(&s1[start + i]) == 0)
		i++;
	len = i;
	if ((new_s = malloc(sizeof(char) * len + 1)) == NULL)
		return ((char *)NULL);
	i = -1;
	while (s1[start + ++i] && i < len)
		new_s[i] = s1[start + i];
	new_s[i] = '\0';
	return (new_s);
}
