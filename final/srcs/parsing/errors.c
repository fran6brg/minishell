/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:48:45 by fberger           #+#    #+#             */
/*   Updated: 2020/02/11 13:58:30 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** pattern_isnt_in_quotes()
*/

int	pattern_isnt_in_quotes(char *line, char *pattern)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (ft_str_start_with(line + i, pattern))
			return (!is_in_quotes(line, i));
	}
	return (0);
}

/*
** parse_error()
**
** handle errors easy to detect
*/

int	parse_error(char *line)
{
	char const	*s = "minishell: syntax error near unexpected token `|'\n";

	if (ft_strlen(line) == 0)
		return (1);
	if (ft_strlen(line) == 1 && line[0] == ';')
		return (ft_putstr_ret("minishell: parse error near `;'\n", 1));
	if (ft_strstr(line, ";;") && pattern_isnt_in_quotes(line, ";;"))
		return (ft_putstr_ret("minishell: parse error near `;;'\n", 1));
	else if (ft_strstr(line, ">>>") && pattern_isnt_in_quotes(line, ">>>"))
		return (ft_putstr_ret("minishell: parse error near `>'\n", 1));
	else if (ft_strstr(line, "<<<") && pattern_isnt_in_quotes(line, "<<<"))
		return (ft_putstr_ret("minishell: parse error near `<'\n", 1));
	else if (ft_str_end_with(line, ">") || ft_str_end_with(line, "<"))
		return (ft_putstr_ret("minishell: parse error near `\\n'\n", 1));
	else if (ft_str_end_with(line, "|"))
		return (ft_putstr_ret(s, 1));
	return (0);
}

/*
** multilines()
**
** check if odd number of quotes
** return 1 if yes so that the command won't be executed
** return 0 otherwise
*/

int	multilines(char *s)
{
	int i;

	if (ft_str_end_with(s, "\\"))
		return (ft_putstr_ret("multilines bonus not handled\n", 1));
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!ft_strchr(s + i + 1, s[i] == '\'' ? '\'' : '"'))
				return (ft_putstr_ret("multilines bonus not handled\n", 1));
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
			while (s[i - 1] == '\\')
				i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
		}
		else if (s[i] == '|')
		{
			i++;
			while (s[i] && is_separator(s[i]))
				i++;
			if (!s[i])
				return (ft_putstr_ret("multilines bonus not handled\n", 1));
		}
	}
	return (0);
}
