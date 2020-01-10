/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 00:36:06 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 21:49:55 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_env *env)
{
	t_env   *var;

    var = env;
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
