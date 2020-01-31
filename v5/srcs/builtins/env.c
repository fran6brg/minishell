/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:25 by fberger           #+#    #+#             */
/*   Updated: 2020/01/31 05:49:20 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*g_env;

/*
** get value from var name
** ft_strequci ci = case insensitive
** pour opti je test d'abord sans trim ce qui évite un malloc
*/

char	*var_value(char *name)
{
	char	*trim;
	t_env	*var;

	var = g_env;
	while (var)
	{
		if (ft_strequci(var->name, name))
			return (var->value);
		var = var->next;
	}
	trim = NULL;
	if (!(trim = ft_strtrim_set(name, "$()")))
		return (0);
	var = g_env;
	while (var)
	{
		if (ft_strequci(var->name, trim))
		{
			ft_strdel(&trim);
			return (var->value);
		}
		var = var->next;
	}
	ft_strdel(&trim);
	return (NULL);
}

/*
** builtin_env()
** print toutes les var d'env
*/

void	builtin_env()
{
	t_env   *var;
	
	var = g_env;
	while (var)
	{
		write(1, var->name, ft_strlen(var->name));
		write(1, "=", 1);
		write(1, var->value, ft_strlen(var->value));
		write(1, "\n", 1);
		var = var->next;
	}
}

/*
** builtin_setenv() ajoute une var d'env
** si elle existe déja, la valeur de la variable est modifiée
** autrement, une nouvelle variable est créée
**
** observations : 
** setenv n'existe pas sur ZSH
*/

int	builtin_setenv(char **cmd_tab)
{
	if (count_arg(cmd_tab) != 3)
	{
		if (!cmd_tab[1])
			builtin_env();
		else
			ft_printf("error: too %s arguments\n", count_arg(cmd_tab) < 3 ? "few" : "much");
		return (0);
	}
	else if (ft_strchr(cmd_tab[1], '='))
	{
		ft_printf("error: variable name can not contain '='\n");
		return (0);
	}
	else if (!push_back_var(cmd_tab))
		return (0);
	return (1);
}

/*
** builtin_unsetenv() supprime toutes les var d'env ayant le même nom.
** si aucune variable ne porte ce nom, le programme ne fait rien
*/


void	 builtin_unsetenv(char **cmd_tab)
{
	t_env	*previous;
	t_env	*current;
	t_env	*next;

	if (count_arg(cmd_tab) == 2)
	{
		current = g_env;
		previous = g_env;
		while (current)
		{
			next = current->next;
			if (ft_strequ(current->name, cmd_tab[1]))
			{
				g_env = (current == g_env) ? next : g_env;
				previous->next = next;
				ft_strdel(&current->name);
				ft_strdel(&current->value);
				free(current);
			}
			previous = current;
			current = current->next;
		}
	}
	else
		ft_printf("error: too %s argument\n", count_arg(cmd_tab) < 3 ? "few" : "much");
}

/*
** builtins_env()
*/

void	builtins_env(char **cmd_tab)
{
	if (ft_strequci(cmd_tab[0], "env"))
		builtin_env();
	else if (ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export"))
	{
		if (!builtin_setenv(cmd_tab))
			free_and_exit(0, "exit: malloc failed\n");
	}
	else if (ft_strequci(cmd_tab[0], "unset"))
		builtin_unsetenv(cmd_tab);
	if (DEBUG)
		printf("end builtins_env\n");
}