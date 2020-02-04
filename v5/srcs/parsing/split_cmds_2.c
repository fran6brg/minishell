/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 06:33:14 by fberger           #+#    #+#             */
/*   Updated: 2020/02/04 14:36:40 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_in_quotes(char *s, int i)
{
	int		j;
	int		inquotes;
	char	lastquote;

	j = -1;
	inquotes = 0;
	lastquote = 0;
	while (s[++j])
	{
		if (!inquotes && (s[j] == '\'' || s[j] == '"'))
		{
			if (i >= 1 && s[j - 1] == '\\')
				;
			else
			{
				lastquote = s[j];
				inquotes = 1;
			}
		}
		else if (inquotes && s[j] == lastquote)
		{
			if (s[j - 1] != '\\' && lastquote == s[j] && j > i)
			{
				printf("s[%d] = %c is inquotes\n", j, s[j]);
				return (1);
			}
			else
				inquotes = 0;
		}
	}
	return (0);
}
