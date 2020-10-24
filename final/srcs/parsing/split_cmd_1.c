/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:50:20 by fberger           #+#    #+#             */
/*   Updated: 2020/02/11 16:46:55 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** check if multilines
** remove (trim) useless ; before and after the *s
** malloc and returns strs array
*/

char	**ft_split_set_quotes_redirects(char *s)
{
	char	**strs;
	char	*trim_s;
	int		str_i;

	if (!s || !(trim_s = ft_strtrim(s, " ;\t")))
		return (NULL);
	if (multilines(trim_s) || !(strs = ft_malloc_str_tab(nb_new_s(trim_s))))
	{
		ft_strdel(&trim_s);
		return (NULL);
	}
	str_i = 0;
	if (!ft_create_strs(trim_s, strs, &str_i))
	{
		ft_strdel(&trim_s);
		ft_free_n_str_tab(strs, str_i);
		return (NULL);
	}
	ft_strdel(&trim_s);
	return (strs);
}
