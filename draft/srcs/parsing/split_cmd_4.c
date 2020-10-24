/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:33:56 by fberger           #+#    #+#             */
/*   Updated: 2020/02/11 16:56:20 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ft_new_str_with_quotes()
**
** strs[*str_i][0] = quote[0]; // premier "
** j = 0; // place 0 reservee au premier "
** k = 0; // nombre d'escape rencontres
*/

int	ft_new_str_with_quotes(char *s, char *quote, char **strs, int *str_i)
{
	int	i;
	int	j;
	int	offset;

	i = -1;
	ft_inc_to_closing_quote(&i, s);
	while (s[i] && !is_separator(s[i]))
		i++;
	if (!(strs[*str_i] = ft_malloc_str(1 + i)))
		return (0);
	strs[*str_i][0] = quote[0];
	j = 0;
	offset = 0;
	while (j < i + 1)
	{
		if (s[j] == '\\' && s[j + 1] == quote[0])
			offset++;
		else
			strs[*str_i][j - offset + 1] = s[j];
		j++;
	}
	strs[*str_i][j - offset + 1] = '\0';
	*str_i += 1;
	return (1);
}

/*
** ft_new_str_redirect()
*/

int	ft_new_str_redirect(char *s, char *quote, char **strs, int *str_i)
{
	int len;

	len = 1 + ((s[0] == '>' && s[1] == '>') ? 1 : 0);
	if (!(strs[*str_i] = ft_malloc_str(len)))
		return (0);
	strs[*str_i][0] = quote[0];
	if (s[1] == '>')
		strs[*str_i][1] = quote[0];
	else
		strs[*str_i][1] = '\0';
	*str_i += 1;
	return (1);
}

/*
** ft_new_str()
*/

int	ft_new_str(char *s, int *i, char **strs, int *str_i)
{
	int		j;
	int		offset;

	j = *i - 1;
	offset = 0;
	while (s[++j] && !is_separator(s[j]) && !is_redirect(s[j]) &&
	!is_quote(s[j]) && s[j] != '|')
		offset += (s[j] == '\\' && (j == 0 || s[j - 1] != '\\')) ? 1 : 0;
	if (!(strs[*str_i] = ft_malloc_str(j - offset - *i)))
		return (0);
	j = *i;
	offset = 0;
	while (s[j] && !is_separator(s[j]) && !is_redirect(s[j]) &&
	!is_quote(s[j]) && s[j] != '|')
	{
		if (s[j] == '\\' && (j == 0 || s[j - 1] != '\\'))
			offset++;
		else
			strs[*str_i][j - offset - *i] = s[j];
		j++;
	}
	*i += ft_strlen(strs[*str_i]) - 1;
	*str_i += 1;
	return (1);
}
