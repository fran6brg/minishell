/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/01/16 02:00:22 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		is_separator(char c, char *set)
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
        // printf("while | s[%d] = %c | nb = %d\n", i, s[i], nb);
		if (s[i] == '\'' || s[i] == '"')
		{
            // printf("first q detected | s[%d] = %c\n", i, s[i]);
			flag = 0;
			nb++;
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
            while (s[i - 1] == '\\')
                i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
            // printf("last q detected | s[%d] = %c\n", i, s[i]);
		}
		else if (s[i] == '>' || s[i] == '<')
		{
            // printf("redirect detected\n");
            flag = 0;
			nb++;
			i += (s[i] == '>' && s[i + 1] == '>') ? 1 : 0;
            i++;
			while (s[i] && is_separator(s[i], set))
				i++;
			j = 0;
			while (s[i + j] && !is_separator(s[i + j], set))
			{
				// printf("filename[%d] = %c\n", j, s[i + j]);
				j++;
			}
			if (j > 0)
				nb++; // filename
			i += j;
		}
		else if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			nb++;
		}
        // printf("end   | s[%d] = %c | nb = %d\n", i, s[i], nb);
	}
    printf("nb_new_s() ret %d\n", nb);
	return (nb);
}

static char		*ft_new_str(const char *s, char *set)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !is_separator(s[i], set) && s[i] != '>' && s[i] != '<')
		i++;
	if (!(new_s = malloc(sizeof(char) * (i + 1))))
		return ((char *)NULL);
	i = 0;
	while (s[i] && !is_separator(s[i], set) && s[i] != '>' && s[i] != '<')
	{
        printf("ptn new_s[%d] = %c\n", i, s[i]);
        new_s[i] = s[i];
        i++;
    }
	new_s[i] = '\0';
	return (new_s);
}

static	char	*ft_new_str_with_quotes(const char *s, char *quote)
{
	int		i;
	char	*new_s;

	i = ft_next_char_pos(s, quote);
	// printf("ft_new_str_with_quotes | i = %d\n", i);
	if (!(new_s = malloc(sizeof(char) * (1 + i + 1))))
		return (NULL);
	i = -1;
	while (s[++i] != quote[0])
		new_s[1 + i] = s[i];
	new_s[0] = quote[0];
	new_s[1 + i] = quote[0];
	new_s[1 + ++i] = '\0';
	return (new_s);
}

static	char	*ft_new_str_redirect(const char *s, char *quote)
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

static int		ft_create_strs(char **strs, const char *s, char *set)
{
	int i;
	int str_i;
	int flag;
    int j;

	i = -1;
	str_i = 0;
	flag = 1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			flag = 0;
            printf("\nft_create_strs | s[%d] = -%c-\n", i, s[i]);
			if (!(strs[str_i] = ft_new_str_with_quotes(s + i + 1, s[i] == '\'' ? "'" : "\"")))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			// printf(">>>>>> strs[%d] = -%s-\n\n", str_i, strs[str_i]);
			str_i++;
			// printf("i += %d", ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\""));
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
			// printf(" > s[%d] = %c\n", i, s[i]);
		}
        else if (s[i] == '<' || s[i] == '>')
        {
            flag = 0;
            printf("\nft_create_strs | s[%d] = -%c-\n", i, s[i]);
			if (!(strs[str_i] = ft_new_str_redirect(s + i + 1, s[i] == '>' ? ">" : "<")))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			str_i++;
			i += (s[i] == '>' && s[i + 1] == '>' ? 1 : 0);
            i += 1;
            while (s[i] && is_separator(s[i], set))
			{
                printf("before filename s[%d] = -%c-\n", j, s[i + j]);
                i++;
            }
			j = 0;
			while (s[i + j] && !is_separator(s[i + j], set))
			{
				printf("filename[%d] = -%c-\n", j, s[i + j]);
				j++;
			}
			if (j > 0)
			{
                printf("\nft_create_strs | s[%d] = -%c-\n", i, s[i]);
                if (!(strs[str_i] = ft_new_str(s + i, set)))
			    {
                    while (str_i-- > 0)
                        free(strs[str_i]);
                    return (0);
			    }
                str_i++;
			    i += j;
            }
        }
		else if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
            printf("\nft_create_strs | s[%d] = -%c-\n", i, s[i]);
			if (!(strs[str_i] = ft_new_str(s + i, set)))
			{
				while (str_i-- > 0)
					free(strs[str_i]);
				return (0);
			}
			// printf("||||||| strs[%d] = -%s-\n\n", str_i, strs[str_i]);
			str_i++;
		}
	}
	return (1);
}

static	int	multiline(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		// printf("multiline | s[%d] = %c\n", i, s[i]);
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!ft_strchr(s + i + 1, s[i] == '\'' ? '\'' : '"'))
			{
				printf("error multiline\n");
				return (1);
			}
			// printf("i += %d", ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\""));
			i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
            while (s[i - 1] == '\\')
                i += ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\"") + 1;
			// printf(" > s[%d] = %c\n", i, s[i]);
		}
	}
	// printf("ok pas de multi\n");
	return (0);
}

char			**ft_split_minishell(char const *s, char *set)
{
	char	**strs;
	char	*trim_s;

	if (!s || multiline(s))
		return (NULL);
	// printf("line = %s\n", s);
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
	// printf("nb_new_s() = %d\n", nb_new_s(trim_s, set));
	strs[nb_new_s(trim_s, set)] = 0;
	ft_strdel(&trim_s);
    print_str_split(strs);
    exit(0);
	return (strs);
}

// echo abc "; ">filename;echo $HOME      '' 

// split ';'

// **1
//  echo abc "; ">filename
//  echo $HOME      ''

// split ' ' with quotes

// 1[0]
//  echo|abc|"; ">filename
// 1[1]
//  echo|$HOME|'' 

// split