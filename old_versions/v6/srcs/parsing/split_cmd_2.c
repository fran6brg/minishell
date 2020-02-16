/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:41:10 by fberger           #+#    #+#             */
/*   Updated: 2020/02/05 11:47:06 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ft_inc_to_closing_quote()
*/

void	ft_inc_to_closing_quote(int *i, char *s)
{
	*i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
	while (s[*i - 1] == '\\')
		*i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
}

/*
** ft_count_chevron_and_filename()
** 	if (j > 0)
**      *nb += 1; // filename
*/

void	ft_count_chevron_and_filename(int *nb, int *i, char *s)
{
	int j;

	*nb += 1;
	*i += (s[*i] == '>' && s[*i + 1] == '>') ? 1 : 0;
	*i += 1;
	while (s[*i] && is_separator(s[*i]))
		*i += 1;
	j = 0;
	while (s[*i + j] && !is_separator(s[*i + j]))
		j += 1;
	if (j > 0)
		*nb += 1;
}

/*
** nb_new_s()
*/

int		nb_new_s(char *s)
{
	int i;
	int nb;
	int flag;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !(flag = 0) && nb++ > 0)
			ft_inc_to_closing_quote(&i, s);
		else if ((s[i] == '>' || s[i] == '<') && !(flag = 0) && nb++ > 0)
			ft_count_chevron_and_filename(&nb, &i, s);
		else if (s[i] == '|' && !(flag = 0))
			nb++;
		else if (is_separator(s[i]))
			flag = 1;
		else if (flag && !(flag = 0))
			nb++;
	}
	return (nb);
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
