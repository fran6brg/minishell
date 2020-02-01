/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 06:33:14 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 07:46:52 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_valid_quote_pattern(char *s, int i, int j)
{
	int k;

	k = j;
	ft_inc_to_closing_quote(&k, s);
	return ((k > i));
}

int		is_in_quotes(char *s, int i)
{
	int j;

	j = -1;
	while (++j < i)
	{
		if (s[j] != '\"' && s[j] != '"')
		{
			if (is_valid_quote_pattern(s, i, j))
				return (1);
		}
	}
	return (0);
}
