/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savesplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 06:33:14 by fberger           #+#    #+#             */
/*   Updated: 2020/01/28 07:06:24 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		nb_new_s_cmds(char *s, char *set)
{
	int i;
	int nb;
	int flag;

	i = -1;
	nb = 0;
	flag = 1;
	while (s[++i])
        if ((s[i] == '\'' || s[i] == '"') && !(flag = 0))
        {
            nb++;
            ft_inc_to_closing_quote(&i, s);
        }
		else if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			nb++;
		}
	return (nb);
}

static char		*ft_create_new_s_cmds(char *s, char *set)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !(is_separator(s[i], set)))
		i++;
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return ((char *)NULL);
	i = -1;
	while (s[++i] && !(is_separator(s[i], set)))
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

/*
**
*/

int	ft_new_str_with_quotes_cmds(char *s, char *quote, char **strs, int *str_i)
{
	int		i;
    int     j;
	int		k;

	i = 1;
	ft_inc_to_closing_quote(&i, s);
	if (!(strs[*str_i] = malloc(sizeof(char) * (1 + i + 1))))
		return (0);
	// printf("s[0] = -%c-\n", s[0]); // s[0] = 1ere lettre apres premier "
	strs[*str_i][0] = quote[0]; // premier "
	j = 0; // place 0 reservee au premier "
	k = 0; // nombre d'escape rencontres
	while (j < i + 1)
	{
		if (s[j] == '\\' && s[j + 1] == quote[0])
			k++;
		else
			strs[*str_i][j - k + 1] = s[j];
		j++;
	}
	strs[*str_i][j - k] = quote[0]; // dernier "
	strs[*str_i][j - k + 1] = '\0';
	*str_i += 1;
	return (1);
}

/*
**
*/

int	ft_str_with_quotes_cmds(char *s, int *i, char **strs, int *str_i)
{
	if (!ft_new_str_with_quotes_cmds(s + *i + 1, s[*i] == '\'' ? "'" : "\"", strs, str_i))
		return (0);
	ft_inc_to_closing_quote(i, s);
	return (1);
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
    {

        if ((s[i] == '\'' || s[i] == '"') && !(flag = 0))
        {
            if (!(ft_str_with_quotes_cmds(s, &i, strs, &str_i)))
                ft_free_n_str_tab_ret(strs, str_i, 0);
            printf(">>>>>>>>>> strs[%d] = %s\n", str_i - 1, strs[str_i - 1]);
        }
		else if (is_separator(s[i], set) || s[i] == ' '|| s[i] == '\t' )
			flag = 1;
		else if (flag)
		{
			flag = 0;
			if (!(strs[str_i] = ft_create_new_s_cmds(s + i, set)))
                ft_free_n_str_tab_ret(strs, str_i, 0);
			str_i++;
            printf(">>>>>>>>>> strs[%d] = %s\n", str_i - 1, strs[str_i - 1]);
		}
    }
	return (1);
}

/*
** ft_split_set() modifié pour tenir compte des quotes
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
	return (strs);
}
