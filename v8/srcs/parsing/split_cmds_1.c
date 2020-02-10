/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 06:33:14 by fberger           #+#    #+#             */
/*   Updated: 2020/02/10 13:44:54 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		is_separator_cmds(char *s, int i, char *set)
{
	int j;

	j = -1;
	while (set[++j])
	{
		if (s[i] == set[j])
			return (1);
	}
	return (0);
}

static int		nb_new_s_cmds(char *s, char *set)
{
	int i;
	int nb;
	int flag;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
	{
		if (is_separator_cmds(s, i, set) && !is_in_quotes(s, i))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			nb++;
		}
	}
	return (nb);
}

static char		*ft_create_new_s(char *s, char *set)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !(is_separator_cmds(s, i, set) && !is_in_quotes(s, i)))
		i++;
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return ((char *)NULL);
	i = -1;
	while (s[++i] && !(is_separator_cmds(s, i, set) && !is_in_quotes(s, i)))
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

static int		ft_create_strs_cmds(char **strs, char *s, char *set)
{
	int i;
	int str_i;
	int flag;

	i = -1;
	str_i = 0;
	flag = 1;
	while (s[++i])
		if (is_separator_cmds(s, i, set) && !is_in_quotes(s, i))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			if (!(strs[str_i] = ft_create_new_s(s + i, set)))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			str_i++;
		}
	return (1);
}

/*
** ft_split_set(";") modifié pour tenir compte des quotes
*/

char			**ft_split_cmds(char *s, char *set)
{
	char	**strs;
	char	*trim_s;

	if (!s)
		return (NULL);
	trim_s = ft_strtrim(s, ";");
	if (!(strs = malloc(sizeof(char *) * (nb_new_s_cmds(trim_s, set) + 1))))
		return (0);
	if (!ft_create_strs_cmds(strs, trim_s, set))
	{
		free(strs);
		return (NULL);
	}
	strs[nb_new_s_cmds(trim_s, set)] = 0;
	ft_strdel(&trim_s);
	if (PARSE)
		ft_print_str_tab(strs, "ft_split_cmds | strs"); // pour debug
	return (strs);
}
