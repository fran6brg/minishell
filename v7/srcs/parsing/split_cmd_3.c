/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 07:13:54 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 12:48:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ft_new_str()
*/

int	ft_new_str(char *s, int *i, char **strs, int *str_i)
{
	int		j;

	j = *i;
	if (PARSE)
		printf("ft_new_strs | s[%d] = %c\n", j, s[j]); // pour debug
	while (s[j] && !is_separator(s[j]) && s[j] != '>'
	&& s[j] != '<' && s[j] != '|')
		j++;
	if (!(strs[*str_i] = malloc(sizeof(char) * (j + 1))))
		return (0);
	j = *i;
	while (s[j] && !is_separator(s[j]) && s[j] != '>'
	&& s[j] != '<' && s[j] != '|')
	{
		strs[*str_i][j - *i] = s[j];
		j++;
	}
	strs[*str_i][j] = '\0';
	if (PARSE)
		printf("ft_new_strs | strs[%d] = %s\n", *str_i, strs[*str_i]); // pour debug
	*i += ft_strlen(strs[*str_i]) - 1;
	*str_i += 1;
	return (1);
}

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
	int	k;

	i = -1;
	// ft_inc_to_closing_quote(&i, s);
	ft_inc_to_end_of_word(&i, s);
	if (!(strs[*str_i] = malloc(sizeof(char) * (1 + i + 1))))
		return (0);
	strs[*str_i][0] = quote[0];
	j = 0;
	k = 0;
	while (j < i + 1)
	{
		if (s[j] == '\\' && s[j + 1] == quote[0])
			k++;
		else
			strs[*str_i][j - k + 1] = s[j];
		j++;
	}
	// strs[*str_i][j - k] = quote[0];
	strs[*str_i][j - k + 1] = '\0';
	*str_i += 1;
	return (1);
}

/*
** ft_str_with_quotes()
*/

int	ft_str_with_quotes(char *s, int *i, char **strs, int *str_i)
{
	if (!ft_new_str_with_quotes(s + *i + 1,
	s[*i] == '\'' ? "'" : "\"", strs, str_i))
		return (0);
	// ft_inc_to_closing_quote(i, s);
	ft_inc_to_end_of_word(i, s);
	return (1);
}

/*
** ft_new_str_chevron()
*/

int	ft_new_str_chevron(char *s, char *quote, char **strs, int *str_i)
{
	if (!(strs[*str_i] = malloc(sizeof(char) *
	(1 + ((s[0] == '>' && s[1] == '>') ? 1 : 0) + 1))))
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
** ft_str_with_chevron()
*/

int	ft_str_with_chevron(char *s, int *i, char **strs, int *str_i)
{
	if (!ft_new_str_chevron(s + *i, s[*i] == '>' ? ">" : "<", strs, str_i))
		return (0);
	*i += (s[*i] == '>' && s[*i + 1] == '>' ? 1 : 0) + 1;
	while (s[*i] && is_separator(s[*i]))
		*i += 1;
	if (!ft_new_str(s, i, strs, str_i))
		return (0);
	// *i += ft_strlen(strs[*str_i - 1]) - 1;
	return (1);
}
