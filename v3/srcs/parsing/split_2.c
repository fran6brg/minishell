/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:41:10 by fberger           #+#    #+#             */
/*   Updated: 2020/01/18 06:44:40 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**
*/

void	ft_inc_to_closing_quote(int *i, char *s)
{
	*i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
    while (s[*i - 1] == '\\')
        *i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
}

/*
**
*/

void	ft_count_chevron_and_filename(int *nb, int *i, char *s, char *set)
{
	int j;

	*nb += 1;
	*i += (s[*i] == '>' && s[*i + 1] == '>') ? 1 : 0;
    *i += 1;
	while (s[*i] && is_separator(s[*i], set))
		*i += 1;
	j = 0;
	while (s[*i + j] && !is_separator(s[*i + j], set))
		j += 1;
	if (j > 0)
		*nb += 1; // filename
}

/*
**
*/

int		nb_new_s(char *s, char *set)
{
	int i;
	int nb;
	int flag;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !(flag = 0))
		{
			nb++;
			ft_inc_to_closing_quote(&i, s);
		}
		else if ((s[i] == '>' || s[i] == '<') && !(flag = 0))
		{
			nb++;
			ft_count_chevron_and_filename(&nb, &i, s, set);
		}
		else if (is_separator(s[i], set))
            flag = 1;
		else if (flag && !(flag = 0))
			nb++;
	}
	return (nb);
}
