/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:48:45 by fberger           #+#    #+#             */
/*   Updated: 2020/01/17 23:53:24 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** handle errors easy to detect
*/

int parse_error(char *line)
{
    if (ft_strstr(line, ";;"))
        return (ft_printf("zsh: parse error near `;;'\n"));
    else if (ft_strstr(line, ">>>"))
        return (ft_printf("zsh: parse error near `>'\n"));
    else if (ft_strstr(line, "<<<")) // "<<"" = bonus
        return (ft_printf("zsh: parse error near `<'\n"));
    else if (ft_str_end_with(line, ">") || ft_str_end_with(line, "<")) // par ex : 'echo abc >'
        return (ft_printf("zsh: parse error near `\\n'\n"));
    else
        return (0);
}

/*
** check if odd number of quotes
** return 1 if yes so that the command won't be executed
** return 0 otherwise
*/

int multilines(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!ft_strchr(s + i + 1, s[i] == '\'' ? '\'' : '"'))
			{
				printf("multilines bonus not handled\n");
				return (1);
			}
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
            while (s[i - 1] == '\\')
                i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
		}
	}
	return (0);
}