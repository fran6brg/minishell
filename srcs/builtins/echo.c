/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/01/11 05:48:17 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** call_var_pattern()
**
** observations :
** echo $PATHfoo renvoie juste un retour à ligne
*/

int call_var_pattern(t_env *env, char *var)
{
	if (var[0] == '$')
	{
		if (is_env_var(env, var + 1))
			ft_printf(var_value(env, var + 1));
		return (1);
	}
	return (0);
}

/*
** echo écrit chaque message sur la sortie standard, avec  un
** espace  entre  chacun  d'eux, et un saut de ligne après le
** dernier.
** option ’-n’ = ne pas effectuer le saut de ligne final.
**
** observations :
** echo -n -n n'affiche rien
*/

void	builtin_echo(t_env *env, char **cmd_tab)
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
				if (call_var_pattern(env, cmd_tab[i]))
					;
				else
					ft_printf("%s", cmd_tab[i]);
				if (cmd_tab[i + 1])
					write(1, " ", 1);
			}
		}
		if (!n_option)
			write(1, "\n", 1);
	}
}
