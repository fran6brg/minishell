/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:41:10 by fberger           #+#    #+#             */
/*   Updated: 2020/01/16 13:31:26 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_back_or_quote(int *flag, int *nb, int *i, char const *s)
{
	*flag = 0;
	*nb += 1;
	*i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
    while (s[*i - 1] == '\\')
        *i += ft_next_char_pos(s + *i + 1, s[*i] == '\'' ? "'" : "\"") + 1;
}

void	ft_is_chevron(int *flag, int *nb, int *i, char const *s, char *set, int *j)
{
	*flag = 0;
	*nb += 1;
	*i += (s[*i] == '>' && s[*i + 1] == '>') ? 1 : 0;
    *i += 1;
	while (s[*i] && is_separator(s[*i], set))
		*i += 1;
	*j = 0;
	while (s[*i + *j] && !is_separator(s[*i + *j], set))
		*j += 1;
	if (*j > 0)
		*nb += 1; // filename
}

int		nb_new_s(char const *s, char *set)
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
        printf("while | s[%d] = -%c- | nb = %d\n", i, s[i], nb);
		if (s[i] == '\'' || s[i] == '"')
			ft_back_or_quote(&flag, &nb, &i, s);
		else if (s[i] == '>' || s[i] == '<')
			ft_is_chevron(&flag, &nb, &i, s, set, &j);
		else if (is_separator(s[i], set))
		{
            // printf("SEP | s[%d] = -%c- | flag = %d | nb = %d\n", i, s[i], flag, nb);
            flag = 1;
        }
		else if (flag)
		{
			flag = 0;
			nb++;
		}
        printf("end   | s[%d] = -%c- | flag = %d | nb = %d\n", i, s[i], flag, nb);
	}
    printf("nb_new_s() ret %d\n", nb);
	return (nb);
}
