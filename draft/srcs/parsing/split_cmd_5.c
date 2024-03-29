/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:33:59 by fberger           #+#    #+#             */
/*   Updated: 2020/02/11 16:44:15 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_separator()
*/

int		is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

/*
** is_separator()
*/

int		is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

/*
** is_separator()
*/

int		is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

/*
** ft_inc_to_closing_quote()
*/

void	ft_inc_to_closing_quote(int *i, char *s)
{
	char quote[2];

	quote[0] = (s[*i] == '\'') ? '\'' : '"';
	quote[1] = '\0';
	*i += ft_next_char_pos(s + *i + 1, quote) + 1;
	while (s[*i - 1] == '\\')
		*i += ft_next_char_pos(s + *i + 1, quote) + 1;
}

/*
** ft_inc_to_end_of_word()
*/

void	ft_inc_to_end_of_word(int *i, char *s)
{
	*i += ft_next_char_pos(s + *i + 1, " \t|><'\"");
	while (s[*i - 1] == '\\' && is_quote(s[*i]))
		*i += ft_next_char_pos(s + *i + 1, " \t|><'\"");
}
