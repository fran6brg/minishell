/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:48:45 by fberger           #+#    #+#             */
/*   Updated: 2020/01/28 07:44:10 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** handle errors easy to detect
*/

int parse_error(char *line)
{
    if (ft_strstr(line, ";;"))
        return (ft_putstr_ret("zsh: parse error near `;;'\n", 1));
    else if (ft_strstr(line, ">>>"))
        return (ft_putstr_ret("zsh: parse error near `>'\n", 1));
    else if (ft_strstr(line, "<<<")) // "<<"" = bonus
        return (ft_putstr_ret("zsh: parse error near `<'\n", 1));
    else if (ft_str_end_with(line, ">") || ft_str_end_with(line, "<")) // par ex : 'echo abc >'
        return (ft_putstr_ret("zsh: parse error near `\\n'\n", 1));
    else
        return (0);
}

/*
** check if odd number of quotes
** return 1 if yes so that the command won't be executed
** return 0 otherwise
*/

int multilines(char *s, char *set)
{
	int i;

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
			while (s[i] && is_separator(s[i], set))
				i++;
			if (!s[i])
				return (ft_putstr_ret("multilines bonus not handled\n", 1));
		}
	}
	return (0);
}