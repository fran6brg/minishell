/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 12:45:47 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_separator()
*/

int		is_separator(char c)
{
	int		i;
	char	*set;

	set = " \t";
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

int		ft_create_strs(char *s, char **strs, int *str_i)
{
	int i;
	int flag;

	i = -1;
	flag = 1;
	while (s[++i])
	{   
		if (PARSE)
			printf("ft_create_strs | s[%d] = %c\n", i, s[i]); // pour debug
		if ((s[i] == '\'' || s[i] == '"') && !(flag = 0))
			ft_str_with_quotes(s, &i, strs, str_i);
		else if ((s[i] == '<' || s[i] == '>') && !(flag = 0))
			ft_str_with_chevron(s, &i, strs, str_i);
		else if (s[i] == '|')
		{
			flag = !is_separator(s[i + 1]);
			ft_str_pipe(strs, str_i);
		}
		else if (is_separator(s[i]))
			flag = 1;
		else if ((flag) && !(flag = 0))
			ft_new_str(s, &i, strs, str_i);
		// if (PARSE)
		// 	ft_print_str_tab(strs, " >>> ft_create_strs | strs"); // pour debug
	}
	return (1);
}

/*
** check if multilines
** remove (trim) useless ; before and after the *s
** malloc and returns strs array
*/

char	**ft_split_set_quotes_chevrons(char *s)
{
	char	**strs;
	char	*trim_s;
	int		str_i;

	if (!s || multilines(s) || !(trim_s = ft_strtrim(s, ";")))
		return (NULL);
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(trim_s) + 1))))
	{
		ft_strdel(&trim_s);
		return (NULL);
	}
	// if (PARSE)
	// 	printf("nb_new_s(trim_s) = %d | %s", nb_new_s(trim_s), trim_s); // pour debug
	str_i = 0;
	if (!ft_create_strs(trim_s, strs, &str_i))
	{
		ft_strdel(&trim_s);
		ft_free_n_str_tab(strs, str_i);
		return (NULL);
	}
	strs[str_i] = NULL;
	ft_strdel(&trim_s);
	if (PARSE)
		ft_print_str_tab(strs, "ft_split_set_quotes_chevrons | strs"); // pour debug
	return (strs);
}
