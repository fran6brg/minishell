/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:34:47 by alamorth          #+#    #+#             */
/*   Updated: 2020/01/19 07:53:44 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**
*/

int	ft_new_str(char *s, char *set, char **strs, int *str_i)
{
	int		i;

	i = 0;
	while (s[i] && !is_separator(s[i], set) && s[i] != '>' && s[i] != '<')
		i++;
	if (!(strs[*str_i] = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (s[i] && !is_separator(s[i], set) && s[i] != '>' && s[i] != '<')
	{
        strs[*str_i][i] = s[i];
        i++;
    }
	strs[*str_i][i] = '\0';
	*str_i += 1;
	return (1);
}

/*
**
*/

int	ft_new_str_with_quotes(char *s, char *quote, char **strs, int *str_i)
{
	int		i;
    int     j;
	int		k;

	i = 1;
	ft_inc_to_closing_quote(&i, s);
	if (!(strs[*str_i] = malloc(sizeof(char) * (1 + i + 1))))
		return (0);
	j = -1;
	k = 0;
	while (++j < i)
	{
		if (s[j] == '\\' && s[j + 1] == quote[0])
			strs[*str_i][1 + k] = s[j++ + 1];
		else
			strs[*str_i][1 + k] = s[j];
		k++;
	}
	strs[*str_i][0] = quote[0];
	strs[*str_i][j + 1] = '\0';
	*str_i += 1;
	return (1);
}

/*
**
*/

int	ft_str_with_quotes(char *s, int *i, char **strs, int *str_i)
{
	if (!ft_new_str_with_quotes(s + *i + 1, s[*i] == '\'' ? "'" : "\"", strs, str_i))
		return (0);
	ft_inc_to_closing_quote(i, s);
	return (1);
}

/*
**
*/

int	ft_new_str_chevron(char *s, char *quote, char **strs, int *str_i)
{
	if (!(strs[*str_i] = malloc(sizeof(char) * (1 + ((s[0] == '>' && s[1] == '>') ? 1 : 0) + 1))))
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
**
*/

int	ft_str_with_chevron(char *s, int *i, char **strs, int *str_i, char *set)
{
	if (!ft_new_str_chevron(s + *i, s[*i] == '>' ? ">" : "<", strs, str_i))
		return (0);
	*i += (s[*i] == '>' && s[*i + 1] == '>' ? 1 : 0) + 1;
    while (s[*i] && is_separator(s[*i], set))
        *i += 1;
    if (!ft_new_str(s + *i, set, strs, str_i))
    	return (0);
    *i += ft_strlen(strs[*str_i - 1]) - 1;
	return (1);
}

/*
**
*/

int	ft_str_pipe(char **strs, int *str_i)
{
	if (!(strs[*str_i] = malloc(sizeof(char) * (1 + 1))))
		return (0);
	strs[*str_i][0] = '|';
    strs[*str_i][1] = '\0';
	*str_i += 1;
	return (1);
}