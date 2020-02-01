/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:53:31 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 02:44:14 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_env_var()
**
** observations :
** echo $PATHfoo renvoie juste un retour à ligne
*/

int is_env_var(char *var)
{
	if (var_value(var))
		return (1);
	return (0);
}

/*
** replace_dollar_vars()
**
** self-explained
*/

void	replace_dollar_vars(char **cmd_tab)
{
	int		i;
	char	*tmp;

    i = 0;
    while (cmd_tab[++i])
	{
		if (is_env_var(cmd_tab[i]))
		{
			if (!(tmp = ft_strdup(var_value(cmd_tab[i]))))
				return ;
			ft_strdel(&cmd_tab[i]);
			cmd_tab[i] = tmp;
		}
	}
}

/*
** push_back_var()
**
** self-explained
*/

int	push_back_var(char **cmd_tab)
{
	t_env   *var;
	t_env   *new;

	var = g_env;
	while (var)
	{
		if (ft_strequ(var->name, cmd_tab[1]))
	 	{
			if (!(var->value = ft_strdup(cmd_tab[2])))
				return (0);
			return (1);
		}
		var = var->next;
	}
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->name = ft_strdup(cmd_tab[1]);
	new->value = ft_strdup(cmd_tab[2]);
	new->next = NULL;
	var = g_env;
	while (var->next)
		var = var->next;
	var->next = new;
	return (1);
}
