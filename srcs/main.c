/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/07 19:56:24 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** print env list
*/

void	print_env(t_env *env_list)
{
	t_env	*elem;
	int		i;

	elem = env_list;
	i = 0;
	while (elem)
	{
		printf("----------------\n%02d->%s = -%s-\n", ++i, elem->name, elem->value);
		elem = elem->next;
	}
}

/*
** store env inside list
*/

int		store_env(char **env, t_env *env_list)
{
	int		i;
	t_env	*elem;
	t_env	*last;
	
	i = -1;
	while (env[++i])
	{
		printf("env[%d] = %s\n", i, env[i]);
		if (!(elem = (t_env *)malloc(sizeof(t_env))))
			return (0);
		elem->name = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		elem->value = ft_substr(env[i], ft_strlen(elem->name) + 1, ft_strlen(env[i]));
		elem->next = NULL;
		if (env_list)
			last->next = elem;
		else
			env_list = elem;
		last = elem;
	}
	return (1);
}

/*
** En C, on peut récupérer l’ensemble des variables d’environment par le 3e
** argument de la fonction main, char **env.
*/

int		main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*cmd;
	// char	*split_cmd;
	
  	(void)argc;
  	(void)argv;
	env_list = NULL;
	store_env(env, env_list);
	print_env(env_list);
	ft_printf("lol");
	while (0)
	{
		get_next_line(0, &cmd);
		// check command validity
		// root through adequat function
	}
	return (0);
}