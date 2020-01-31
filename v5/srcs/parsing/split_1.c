/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/01/31 06:17:28 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_separator()
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
** ft_create_strs()
*/

int		ft_create_strs(char *s, char **strs, int *str_i, char *set)
{
	int i;
	int flag;
	int	ret;

	i = -1;
	flag = 1;
	ret = 1;
	while (s[++i])
	{

		if (DEBUGPARSE)
			printf("ft_create_strs | s[%d] = -%c- | flag = %d\n", i, s[i], flag);
		if ((s[i] == '\'' || s[i] == '"') && !(flag = 0))
			ret = ft_str_with_quotes(s, &i, strs, str_i);
        else if ((s[i] == '<' || s[i] == '>') && !(flag = 0))
			ret = ft_str_with_chevron(s, &i, strs, str_i, set);
		else if (s[i] == '|')
		{
			flag = !is_separator(s[i + 1], set);
			ret = ft_str_pipe(strs, str_i);
		}
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

char			**ft_split_set_quotes_chevrons(char *s, char *set)
{
	char	**strs;
	char	*trim_s;
	int		str_i;

	if (!s || multilines(s, set) || !(trim_s = ft_strtrim(s, ";")))
		return (NULL);
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(trim_s, set) + 1))))
	{
		ft_strdel(&trim_s);
		return (NULL);
	}
	str_i = 0;
	if (!ft_create_strs(trim_s, strs, &str_i, set))
	{
		ft_strdel(&trim_s);
		ft_free_n_str_tab(strs, str_i);
		return (NULL);
	}
	// printf("nb_new_s(trim_s, set) = %d\n", nb_new_s(trim_s, set));
	// printf("str_i = %d\n", str_i);
	strs[str_i] = NULL;
	ft_strdel(&trim_s);
	return (strs);
}