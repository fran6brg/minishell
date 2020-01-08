/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 04:45:15 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** echo et l’option ’-n’
** cas particuliers :
** . echo -n -n n'affiche rien
*/

void	builtin_echo(char **cmd_tab)
{
	int i;
	int	n_option;

	i = 0;
	n_option = 0;
	if (cmd_tab[1] == 0)
		write(1, "\n", 1);
	else
	{
		while (cmd_tab[++i])
		{
			if ((i == 1 || (i > 1 && !ft_strcmp(cmd_tab[i - 1], "-n")))
			&& !ft_strcmp(cmd_tab[i], "-n"))
				n_option = 1;
			else
			{
				ft_printf("%s", cmd_tab[i]);
				if (cmd_tab[i + 1])
					write(1, " ", 1);
			}
		}
		if (!n_option)
			write(1, "\n", 1);
	}
}
