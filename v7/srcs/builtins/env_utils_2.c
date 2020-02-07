/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 10:15:02 by fberger           #+#    #+#             */
/*   Updated: 2020/02/07 11:13:38 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
** swap_var_data()
*/

void		swap_var_data(t_env *var_j, t_env *var_j_next)
{
	char *tmp_name;
	char *tmp_value;

    tmp_name = ft_strdup(var_j->name);
    ft_strdel(&var_j->name);
    var_j->name = ft_strdup(var_j_next->name);
    
    tmp_value = ft_strdup(var_j->value);
    ft_strdel(&var_j->value);
    var_j->value = ft_strdup(var_j_next->value);
    
    ft_strdel(&var_j_next->name);
    var_j->next->name = ft_strdup(tmp_name);
    ft_strdel(&tmp_name);
    
    ft_strdel(&var_j_next->value);
    var_j->next->value = ft_strdup(tmp_value);
    ft_strdel(&tmp_value);

}

/*
** sort_env_var()
*/

void    sort_env_var(void)
{
	t_env	*var_i;
    t_env	*var_j;

    var_i = g_env;
	while (var_i)
	{
		var_j = g_env;
		while (var_j)
		{
			if (var_j->next && ft_strcmp(var_j->name, var_j->next->name) > 0)
                swap_var_data(var_j, var_j->next);
			var_j = var_j->next;
		}
		var_i = var_i->next;
	}
}

/*
** display_declared_vars()
*/

void    display_declared_vars(void)
{
	t_env	*var;

	var = g_env;
    sort_env_var();
	while (var)
	{
		write(1, "declare -x ", 11);
        write(1, var->name, ft_strlen(var->name));
		write(1, "=\"", 1);
		write(1, var->value, ft_strlen(var->value));
		write(1, "\n", 1);
		var = var->next;
	}
}
