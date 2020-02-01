/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 05:17:57 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** echo écrit chaque message sur la sortie standard, avec un
** espace  entre  chacun  d'eux, et un saut de ligne après le
** dernier.
** option ’-n’ = ne pas effectuer le saut de ligne final.
**
** observations :
** echo -n -n n'affiche rien
*/

void	builtin_echo(char **cmd_tab)
{
	int		i;
	char	**args;

	i = 0;
	if (cmd_tab[1] == 0)
		write(1, "\n", 1);
	else
	{
		args = format_args(cmd_tab);
		i = 0;
		while (args[++i])
		{
			if (is_n_option(i, args))
				continue ;
			if (i > 1 && !is_n_option(i - 1, args))
				write(1, " ", 1);
			if (is_env_var(args[i]))
				ft_putstr(var_value(args[i] + 1));
			else if (arg_is_in_quotes(args[i]))
				write(1, args[i] + 1, ft_strlen(args[i]) - 2);
			else
				write(1, args[i], ft_strlen(args[i]));
		}
		write(1, "\n", no_option_n(args));
	}
}
