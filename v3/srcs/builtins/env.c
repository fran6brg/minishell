/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:25 by fberger           #+#    #+#             */
/*   Updated: 2020/01/19 04:19:50 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*g_env;

/*
** get value from var name
*/

char	*var_value(char *name)
{
	t_env			*var;

	var = g_env;
	while (var)
	{
		if (ft_strequci(var->name, name))
			return (var->value);
		var = var->next;
	}
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
		ft_printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
}

/*
** builtin_setenv() ajoute une var d'env
** si elle existe déja, la valeur de la variable est modifiée
** autrement, une nouvelle variable est créée
**
** observations : 
** setenv n'existe pas sur ZSH, à la place il y a export Name=Value
*/

int	builtin_setenv(char **cmd_tab)
{
	t_env   *var;
	t_env   *new;

	if (count_arg(cmd_tab) != 3)
	{
		if (!cmd_tab[1])
			builtin_env();
		else
			ft_printf("error: too %s argument\n", count_arg(cmd_tab) < 3 ? "few" : "much");
		return (1);
	}
	else if (ft_strchr(cmd_tab[1], '='))
	{
		ft_printf("error: variable name can not contain '='\n");
		return (1);
	}
	var = g_env;
	while (var)
	{
		if (ft_strequ(var->name, cmd_tab[1]))
	 	{
			var->value = ft_strdup(cmd_tab[2]);
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

/*
** builtin_unsetenv() supprime toutes les var d'env ayant le même nom.
** si aucune variable ne porte ce nom, le programme ne fait rien
*/


void	 builtin_unsetenv(char **cmd_tab)
{
	t_env	*previous;
	t_env	*current;
	t_env	*next;

	if (count_arg(cmd_tab) != 2)
	{
		ft_printf("error: too %s argument\n", count_arg(cmd_tab) < 3 ? "few" : "much");
		return ;
	}
	current = g_env;
	previous = g_env;
	while (current)
	{
		next = current->next;
		if (ft_strequ(current->name, cmd_tab[1]))
		{
			if (current == g_env)
				g_env = next;
			previous->next = next;
			ft_strdel(&current->name);
			ft_strdel(&current->value);
			free(current);
		}
		previous = current;
		current = current->next;
	}
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
}