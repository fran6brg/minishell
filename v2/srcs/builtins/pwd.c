/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 00:36:06 by fberger           #+#    #+#             */
/*   Updated: 2020/01/18 22:54:23 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** global var for put_promt()
*/

t_env	*g_env;

void	builtin_pwd()
{
	t_env   *var;

    var = g_env;
	while (var)
	{
		if (ft_strequci(var->name, "PWD"))
		{
			ft_printf("%s\n", var->value);
			return ;
		}
		var = var->next;
	}
}
