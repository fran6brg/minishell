/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:17 by fberger           #+#    #+#             */
/*   Updated: 2020/01/28 06:33:06 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_separator(char c, char *set)
{
	int i;

	i = -1;
	while (set[++i])
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

static int		nb_new_s(char const *s, char *set)
{
	int i;
	int nb;
	int flag;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
		if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			nb++;
		}
	return (nb);
}

static char		*ft_create_new_s(const char *s, char *set)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !(is_separator(s[i], set)))
		i++;
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return ((char *)NULL);
	i = -1;
	while (s[++i] && !(is_separator(s[i], set)))
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

static int		ft_create_strs(char **strs, const char *s, char *set)
{
	int i;
	int str_i;
	int flag;

	i = -1;
	str_i = 0;
	flag = 1;
	while (s[++i])
		if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			if (!(strs[str_i] = ft_create_new_s(s + i, set)))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			str_i++;
		}
	return (1);
}

char			**ft_split_set(char const *s, char *set)
{
	char	**strs;
	char	*trim_s;

	if (!s)
		return (NULL);
	trim_s = ft_strtrim(s, ";");
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(trim_s, set) + 1))))
		return (0);
	if (!ft_create_strs(strs, trim_s, set))
	{
		free(strs);
		return (NULL);
	}
	strs[nb_new_s(trim_s, set)] = 0;
	ft_strdel(&trim_s);
	return (strs);
}
