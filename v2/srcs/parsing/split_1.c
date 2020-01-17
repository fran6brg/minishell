/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/01/17 14:14:17 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_separator(char c, char *set)
{
	int i;

	i = -1;
	while (set[++i])
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

char		*ft_new_str(const char *s, char *set)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !is_separator(s[i], set) && s[i] != '>' && s[i] != '<')
		i++;
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && !is_separator(s[i], set) && s[i] != '>' && s[i] != '<')
	{
        new_s[i] = s[i];
        i++;
    }
	new_s[i] = '\0';
	return (new_s);
}

int		ft_next_char_posS(const char *s, char *set)
{
	int		i;
	int		j;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (set[++j])
			if (s[i] == set[j] && s[i - 1] != '\\')
				return (i);
	}
	return (i);
}

char	*ft_new_str_with_quotes(const char *s, char *quote)
{
	int		i;
	char	*new_s;
    int     j;
	int		k;

	i = ft_next_char_posS(s, quote) + 1;
	if (!(new_s = malloc(sizeof(char) * (1 + i + 1))))
		return (NULL);
	j = -1;
	k = 0;
	while (++j < i)
	{
		if (s[j] == '\\' && s[j + 1] == '"')
		{
			new_s[1 + k] = s[j + 1];
			j++;
		}
		else
			new_s[1 + k] = s[j];
		k++;
	}
	new_s[0] = quote[0];
	new_s[j + 1] = '\0';
	return (new_s);
}

char	*ft_new_str_chevron(const char *s, char *quote)
{
	char	*new_s;

	// printf("ft_new_str_with_quotes | i = %d\n", i);
	if (!(new_s = malloc(sizeof(char) * (1 + ((s[0] == '>' && s[1] == '>') ? 1 : 0) + 1))))
		return (NULL);
	new_s[0] = quote[0];
    if (s[1] == '>')
	    new_s[1] = quote[0];
	else
        new_s[1] = '\0';
	return (new_s);
}

char			**ft_split_set_quotes_chevron(char const *s, char *set)
{
	char	**strs;
	char	*trim_s;

	if (!s || multiline(s))
		return (NULL);
	trim_s = ft_strtrim(s, ";");
	if (!(strs = malloc(sizeof(char *) * (nb_new_s(trim_s, set) + 1))))
	{
		ft_strdel(&trim_s);
		return (0);
	}
	if (!ft_create_strs(strs, trim_s, set))
	{
		ft_strdel(&trim_s);
		free(strs);
		return (NULL);
	}
	strs[nb_new_s(trim_s, set)] = 0;
	ft_strdel(&trim_s);
	return (strs);
}