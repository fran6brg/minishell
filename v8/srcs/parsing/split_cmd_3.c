/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 07:13:54 by fberger           #+#    #+#             */
/*   Updated: 2020/02/10 19:24:17 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ft_str_with_quotes()
*/

int	ft_str_with_quotes(char *s, int *i, char **strs, int *str_i)
{
	char quote[2];

	quote[0] = (s[*i] == '\'') ? '\'' : '"';
	quote[1] = '\0';
	if (PARSE)
		printf("  >> ft_str_with_quotes | s[%d] = %c\n", *i, s[*i]); // pour debug
	if (!ft_new_str_with_quotes(s + *i + 1, quote, strs, str_i))
		return (0);
	ft_inc_to_closing_quote(i, s);
	while (s[*i] && !is_separator(s[*i]))
		*i += 1;
	if (PARSE)
		printf("     ft_str_with_quotes | s[%d] = %c\n", *i, s[*i]); // pour debug
	return (1);
}

/*
** ft_str_with_redirect()
*/

int	ft_str_with_redirect(char *s, int *i, char **strs, int *str_i)
{
	if (!ft_new_str_redirect(s + *i, s[*i] == '>' ? ">" : "<", strs, str_i))
		return (0);
	*i += (s[*i] == '>' && s[*i + 1] == '>' ? 1 : 0) + 1;
	while (s[*i] && is_separator(s[*i]))
		*i += 1;
	if (!ft_new_str(s, i, strs, str_i))
		return (0);
	return (1);
}

/*
** ft_str_pipe()
*/

int		ft_str_pipe(char **strs, int *str_i)
{
	if (!(strs[*str_i] = malloc(sizeof(char) * (1 + 1))))
		return (0);
	strs[*str_i][0] = '|';
	strs[*str_i][1] = '\0';
	*str_i += 1;
	return (1);
}

/*
** ft_create_strs()
*/

int		ft_create_strs(char *s, char **strs, int *str_i)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (PARSE)
			printf(">> s[%d] = %c | *str_i = %d\n", i, s[i], *str_i); // pour debug
		if (is_quote(s[i]))
			ft_str_with_quotes(s, &i, strs, str_i);
		else if (is_redirect(s[i]))
			ft_str_with_redirect(s, &i, strs, str_i);
		else if (s[i] == '|')
			ft_str_pipe(strs, str_i);
		else if (is_separator(s[i]))
			;
		else
			ft_new_str(s, &i, strs, str_i);
		if (PARSE)
			printf("   s[%d] = %c\n", i, s[i]); // pour debug
		if (PARSE)
			printf(" -------- ft_create_strs | strs[%d] = %s\n\n", *str_i - 1, strs[*str_i - 1]); // pour debug
	}
	return (1);
}