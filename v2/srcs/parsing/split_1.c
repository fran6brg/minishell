/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/01/16 13:48:33 by alamorth         ###   ########.fr       */
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

char	*ft_new_str_with_quotes(const char *s, char *quote)
{
	int		i;
	char	*new_s;
    int     j;

	i = ft_next_char_pos(s, quote) + 1;
    while (s[i - 1] == '\\')
        i += ft_next_char_pos(s + i + 1, quote) + 1;
	if (!(new_s = malloc(sizeof(char) * (1 + i + 1))))
		return (NULL);
	j = -1;
	while (++j < i)
		new_s[1 + j] = s[j];
	new_s[0] = quote[0];
	//new_s[1 + j] = quote[0];
	new_s[1 + j] = '\0';
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