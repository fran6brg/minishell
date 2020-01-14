/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set_and_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:17 by fberger           #+#    #+#             */
/*   Updated: 2020/01/14 16:59:46 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
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
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			flag = 0;
			nb++;
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"");
		}
		else if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			nb++;
		}
	}
	return (nb);
}

static char		*ft_new_str(const char *s, char *set)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !(is_separator(s[i], set)))
		i++;
	printf("ft_new_str | i = %d\n", i);
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return ((char *)NULL);
	i = -1;
	while (s[++i] && !(is_separator(s[i], set)))
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

static	char	*ft_new_str_with_quotes(const char *s, char *quote)
{
	int		i;
	char	*new_s;

	i = ft_next_char_pos(s, quote);
	printf("ft_new_str_with_quotes | i = %d\n", i);
	if (!(new_s = malloc(sizeof(char) * (1 + i + 1))))
		return (NULL);
	i = -1;
	while (s[++i] != quote[0])
		new_s[1 + i] = s[i];
	new_s[0] = quote[0];
	new_s[1 + i] = quote[0];
	new_s[1 + ++i] = '\0';
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
	{
		printf("\nft_create_strs | s[%d] = %c\n", i, s[i]);
		if (s[i] == '\'' || s[i] == '"')
		{
			flag = 0;
			if (!(strs[str_i] = ft_new_str_with_quotes(s + i + 1, s[i] == '\'' ? "'" : "\"")))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			printf(">>>>>> strs[%d] = -%s-\n\n", str_i, strs[str_i]);
			str_i++;
			printf("i += %d", ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\""));
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
			printf(" > s[%d] = %c\n", i, s[i]);
		}
		else if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			if (!(strs[str_i] = ft_new_str(s + i, set)))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			printf("||||||| strs[%d] = -%s-\n\n", str_i, strs[str_i]);
			str_i++;
		}
	}
	return (1);
}

static	int	multiline(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		printf("multiline | s[%d] = %c\n", i, s[i]);
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!ft_strchr(s + i + 1, s[i] == '\'' ? '\'' : '"'))
			{
				printf("error multiline\n");
				return (1);
			}
			printf("i += %d", ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\""));
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
			printf(" > s[%d] = %c\n", i, s[i]);
		}
	}
	printf("ok pas de multi\n");
	return (0);
}

char			**ft_split_set_and_quotes(char const *s, char *set)
{
	char	**strs;
	char	*trim_s;

	if (!s || multiline(s))
		return (NULL);
	printf("line = %s\n", s);
	trim_s = ft_strtrim(s, ";");
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(trim_s, set) + 1))))
	{
		ft_strdel(&trim_s);
		return (0);
	}
	if (!ft_create_strs(strs, trim_s, set))
	{
		ft_strdel(&trim_s);
		free(strs);
		return (NULL);
	}
	printf("nb_new_s() = %d\n", nb_new_s(trim_s, set));
	strs[nb_new_s(trim_s, set)] = 0;
	ft_strdel(&trim_s);
	return (strs);
}
