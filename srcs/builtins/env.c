/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:25 by fberger           #+#    #+#             */
/*   Updated: 2020/01/09 01:50:29 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** args_control() vérifie que la commande shell (splitée via les ' ')
** contient bien le nombre approprié d'argument (donné par x)
*/

int args_control(char **cmds, int x)
{
  int i;

  i = 0;
  while (cmds[i] != 0)
    i++;
  if (i == x &&
      (ft_strcmp(cmds[1], "PATH") == 0 || ft_strcmp(cmds[1], "HOME") ||
       ft_strcmp(cmds[1], "PWD") == 0))
      return (ft_printf("cd: permission denied\n"));
  if (i != x)
    return (-1);
  return (0);
}

void	builtin_env(char **cmd_tab)
{
    print_str_split(cmd_tab);
    ;
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

	if (args_control(cmd_tab, 3))
		return ;
	var = env;
	while (var)
	{
		if (!ft_strcmp(var->name, cmd_tab[1]))
	 	{
			var->value = ft_strdup(cmd_tab[2]);
			return ;
		}
		var = var->next;
	}
	var = env;
	while (var->next)
		var = var->next;
	if (!(new = (t_env *)malloc(sizeof(t_env) * 1)))
		return ;
	new->name = ft_strdup(cmd_tab[1]);
	new->value = ft_strdup(cmd_tab[2]);
	new->next = NULL;
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

	if (args_control(cmd_tab, 2))
		return ;
	current = env;
	previous = env;
	while (current)
	{
		next = current->next;
		if (!ft_strcmp(current->name, cmd_tab[1]))
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
