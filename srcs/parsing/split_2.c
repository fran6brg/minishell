/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:41:10 by fberger           #+#    #+#             */
/*   Updated: 2020/01/16 04:48:07 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		nb_new_s(char const *s, char *set)
{
	int i;
	int nb;
	int flag;
	int	j;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
	{
        printf("while | s[%d] = -%c- | nb = %d\n", i, s[i], nb);
		if (s[i] == '\'' || s[i] == '"')
		{
			flag = 0;
			nb++;
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
            while (s[i - 1] == '\\')
                i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
		}
		else if (s[i] == '>' || s[i] == '<')
		{
            flag = 0;
			nb++;
			i += (s[i] == '>' && s[i + 1] == '>') ? 1 : 0;
            i++;
			while (s[i] && is_separator(s[i], set))
				i++;
			j = 0;
			while (s[i + j] && !is_separator(s[i + j], set))
				j++;
			if (j > 0)
				nb++; // filename
		}
		else if (is_separator(s[i], set))
		{
            // printf("SEP | s[%d] = -%c- | flag = %d | nb = %d\n", i, s[i], flag, nb);
            flag = 1;
        }
		else if (flag)
		{
			flag = 0;
			nb++;
		}
        printf("end   | s[%d] = -%c- | flag = %d | nb = %d\n", i, s[i], flag, nb);
	}
    printf("nb_new_s() ret %d\n", nb);
	return (nb);
}
