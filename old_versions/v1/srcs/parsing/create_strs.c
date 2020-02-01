/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:34:47 by alamorth          #+#    #+#             */
/*   Updated: 2020/01/16 13:48:05 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_str_backs_quotes(const char *s, int *i, int *str_i, char **strs)
{
    printf("\nft_new_str_with_quotes | s[%d] = -%c-\n", *i, s[*i]);
	if (!(strs[*str_i] = ft_new_str_with_quotes(s + *i + 1, s[*i] == '\'' ? "'" : "\"")))
	{
		while (*str_i-- > 0)
			free(strs[*str_i]);
		return (0);
	}
		// printf(">>>>>> strs[%d] = -%s-\n\n", str_i, strs[str_i]);
	*str_i += 1;
			// printf("i += %d", ft_next_char_pos(s + i + 1, s[i] == '\'' ? "'" : "\""));
	*i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
    while (s[*i - 1] == '\\')
        *i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
			// printf(" > s[%d] = %c\n", i, s[i]);
	return (1);
}

int			ft_str_chevron(const char *s, int *i, int *str_i, char **strs, char *set)
{
	printf("\nft_new_str_chevron | s[%d] = -%c-\n", *i, s[*i]);
	if (!(strs[*str_i] = ft_new_str_chevron(s + *i, s[*i] == '>' ? ">" : "<")))
	{
		while (*str_i-- > 0)
			free(strs[*str_i]);
		return (0);
	}
	*str_i += 1;
	*i += (s[*i] == '>' && s[*i + 1] == '>' ? 1 : 0);
    *i += 1;
    while (s[*i] && is_separator(s[*i], set))
        *i += 1;
    printf("\nft_new_str filename | s[%d] = -%c-\n", *i, s[*i]);
    if (!(strs[*str_i] = ft_new_str(s + *i, set)))
    {
        while (*str_i-- > 0)
            free(strs[*str_i]);
        return (0);
    }
    *i += ft_strlen(strs[*str_i]) - 1;
    *str_i += 1;
	return (1);
}

int			ft_is_flag(const char *s, int *i, int *str_i, char **strs, char *set)
{
	printf("\nft_new_str | s[%d] = -%c-\n", *i, s[*i]);
	if (!(strs[*str_i] = ft_new_str(s + *i, set)))
	{
		while (*str_i-- > 0)
			free(strs[*str_i]);
		return (0);
	}
	// printf("||||||| strs[%d] = -%s-\n\n", str_i, strs[str_i]);
	*str_i += 1;
	return (1);
}

int		ft_create_strs(char **strs, const char *s, char *set)
{
	int i;
	int str_i;
	int flag;
    // int j;

	i = -1;
	str_i = 0;
	flag = 1;
	while (s[++i])
	{
        printf("while create | s[%d] = -%c-\n", i, s[i]);
		if (s[i] == '\'' || s[i] == '"')
		{
			flag = 0;
			if (ft_str_backs_quotes(s, &i, &str_i, strs) == 0)
				return (0);
			
		}
        else if (s[i] == '<' || s[i] == '>')
        {
			flag = 0;
			if (ft_str_chevron(s, &i, &str_i, strs, set) == 0)
				return (0);
        }
		else if (is_separator(s[i], set))
			flag = 1;
		else if (flag)
		{
			flag = 0;
			if (ft_is_flag(s, &i, &str_i, strs, set) == 0)
				return (0);
		}
	}
	return (1);
}