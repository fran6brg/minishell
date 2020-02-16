/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:53:42 by fberger           #+#    #+#             */
/*   Updated: 2020/02/08 14:04:58 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_n_option()
*/

int		is_n_option(int i, char **cmd_tab)
{
	int	j;
	int	k;

	j = 0;
	while (++j <= i)
	{
		if (!ft_str_start_with(cmd_tab[j], "-n"))
			return (0);
		k = 1;
		while (cmd_tab[j][++k])
		{
			if (cmd_tab[j][k] != 'n')
				return (0);
		}
	}
	return (1);
}

/*
** no_option_n()
**
** NB :
** echo a b c -n l'option doit se situer avant les arguments donc
** else if (i > 1)
**    return (0);
*/

int		no_option_n(char **cmd_tab)
{
	int i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (is_n_option(i, cmd_tab))
			return (0);
		else if (i > 1)
			return (1);
	}
	return (1);
}
