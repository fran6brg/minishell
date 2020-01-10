/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:17 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 19:23:58 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_separator(char c, char separator)
{
	if (c == separator)
		return (1);
	return (0);
}

static int		nb_new_s(char const *s, char separator)
{
	int i;
	int nb;
	int flag;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
		if (is_separator(s[i], separator))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			nb++;
		}
	return (nb);
}

static char		*ft_create_new_s(const char *s, char separator)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !(is_separator(s[i], separator)))
		i++;
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return ((char *)NULL);
	i = -1;
	while (s[++i] && !(is_separator(s[i], separator)))
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

static int		ft_create_strs(char **strs, const char *s, char separator)
{
	int i;
	int str_i;
	int flag;

	i = -1;
	str_i = 0;
	flag = 1;
	while (s[++i])
		if (is_separator(s[i], separator))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			if (!(strs[str_i] = ft_create_new_s(s + i, separator)))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			str_i++;
		}
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(s, c) + 1))))
		return (0);
	if (!ft_create_strs(strs, s, c))
	{
		free(strs);
		return (NULL);
	}
	strs[nb_new_s(s, c)] = 0;
	return (strs);
}
