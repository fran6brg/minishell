/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:53:31 by fberger           #+#    #+#             */
/*   Updated: 2020/01/19 01:54:29 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_env_var()
** ft_strequci str equal case insensitive
*/

int		is_env_var(char *arg)
{
	t_env   *var;
	
	var = g_env;
	while (var)
	{
		if (ft_strequci(var->name, arg))
			return (1);
		var = var->next;
	}
	return (0);
}

/*
** is_dollar_env_var()
**
** observations :
** echo $PATHfoo renvoie juste un retour à ligne
*/

int is_dollar_env_var(char *var)
{
	if (var[0] == '$')
	{
		if (is_env_var(var + 1))
			return (1);
	}
	return (0);
}
