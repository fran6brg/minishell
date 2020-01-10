/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:25 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 20:37:52 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_env *env)
{
	t_env   *var;
	
	var = env;
	while (var)
	{
		ft_printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
}

/*
** builtin_setenv() ajoute une var d'env
** Si elle existe déja, la valeur de la variable est modifiée
** Autrement, une nouvelle variable est créée
** NB : setenv n'existe pas sur ZSH, à la place il y a export Name=Value
*/

void    builtin_setenv(char **cmd_tab, t_env *env)
{
	t_env   *var;
	t_env   *new;

	if (nb_arg(cmd_tab) != 3)
		return ;
	var = env;
	while (var)
	{
		if (ft_strequ(var->name, cmd_tab[1]))
	 	{
			var->value = ft_strdup(cmd_tab[2]);
			return ;
		}
		var = var->next;
	}
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return ;
	new->name = ft_strdup(cmd_tab[1]);
	new->value = ft_strdup(cmd_tab[2]);
	new->next = NULL;
	var = env;
	while (var->next)
		var = var->next;
	var->next = new;
}

/*
** builtin_unsetenv() supprime toutes les var d'env ayant le même nom.
** si aucune variable ne porte ce nom, le programme ne fait rien
*/


void	 builtin_unsetenv(char **cmd_tab, t_env *env)
{
	t_env	 *previous;
	t_env	 *current;
	t_env	 *next;

	if (nb_arg(cmd_tab) != 2)
		return ;
	current = env;
	previous = env;
	while (current)
	{
		next = current->next;
		if (ft_strequ(current->name, cmd_tab[1]))
		{
			if (current == env)
				env = next;
			previous->next = next;
			ft_strdel(&current->name);
			ft_strdel(&current->value);
			free(current);
		}
		previous = current;
		current = current->next;
	}
}
