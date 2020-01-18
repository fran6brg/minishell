/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/01/18 04:18:09 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**
*/

int		is_separator(char c, char *set)
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

/*
**
*/

int		ft_next_char_posS(const char *s, char *set)
{
	int		i;
	int		j;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (set[++j])
			if (s[i] == set[j] && s[i - 1] != '\\')
				return (i);
	}
	return (i);
}


/*
**
*/

int		ft_create_strs(char **strs, const char *s, int *str_i, char *set)
{
	int i;
	int flag;
	int	ret;

	i = -1;
	flag = 1;
	ret = 1;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !(flag = 0))
			ret = ft_str_with_quotes(s, &i, strs, str_i);
        else if ((s[i] == '<' || s[i] == '>') && !(flag = 0))
			ret = ft_str_with_chevron(s, &i, strs, str_i, set);
		else if (is_separator(s[i], set))
			flag = 1;
		else if ((flag) && !(flag = 0))
			ret = ft_new_str(s + i, set, strs, str_i);
		if (!ret)
			return (0);
	}
	return (1);
}

/*
** check if multilines
** remove (trim) useless ; before and after the *s
** malloc and returns strs array
*/

char			**ft_split_set_quotes_chevrons(char const *s, char *set)
{
	char	**strs;
	char	*trim_s;
	int		str_i;

	if (!s || multilines(s))
		return (NULL);
	trim_s = ft_strtrim(s, ";");
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(trim_s, set) + 1))))
	{
		ft_strdel(&trim_s);
		return (NULL);
	}
	str_i = 0;
	if (!ft_create_strs(strs, trim_s, &str_i, set))
	{
		ft_strdel(&trim_s);
		ft_free_str_tab(strs, str_i);
		return (NULL);
	}
	strs[str_i] = 0;
	ft_strdel(&trim_s);
	return (strs);
}