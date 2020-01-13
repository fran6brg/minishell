/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/13 16:06:25 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** root towards the right function
*/

void	root(t_env *env, char *path, char **cmd_tab)
{
	// print_str_split(cmd_tab);
	// printf("path = %s\n", path);
	if (ft_strequci(cmd_tab[0], "echo"))
		builtin_echo(env, cmd_tab);
	else if (ft_strequci(cmd_tab[0], "cd"))
		builtin_cd(env, cmd_tab);
	else if (ft_strequci(cmd_tab[0], "pwd"))
		builtin_pwd(env);
	else if (ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export"))
		builtin_setenv(cmd_tab, env);
	else if (ft_strequci(cmd_tab[0], "unset"))
		builtin_unsetenv(cmd_tab, env);
	else if (ft_strequci(cmd_tab[0], "env"))
		builtin_env(env);
	else if (ft_strequci(cmd_tab[0], "exit"))
	{
		free_env(env);
		exit(1);
	}
	else if (cmd_tab[0]) // pour protéger contre la commade chaine d'espaces + enter
		execute(cmd_tab, path);
}

/*
** get value from var name
*/

char	*var_value(t_env *env, char *name)
{
	t_env	*var;

	var = env;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

/*
** store env inside list
*/

int		store_env(char **env_tab, t_env **env)
{
	int		i;
	t_env	*var;
	t_env	*last;
	
	i = -1;
	last = NULL;
	while (env_tab[++i])
	{
		if (!(var = (t_env *)malloc(sizeof(t_env))))
			return (0);
		var->name = ft_substr(env_tab[i], 0, (int)(ft_strchr(env_tab[i], '=') - env_tab[i]));
		var->value = ft_substr(env_tab[i], (int)(ft_strchr(env_tab[i], '=') - env_tab[i]) + 1, ft_strlen(env_tab[i]));
		var->next = NULL;
		if (last)
			last->next = var;
		else
			*env = var;
		last = var;
	}
	return (1);
}

/*
** 3e argument de la fonction main == l’ensemble des variables d’environment
*/

int		main(int argc, char **argv, char **env_tab)
{
	t_env	*env;
	char	*line;
	char	**cmds;
	char	**cmd_tab;
	int		i;
	
	if (argc > 1 && argv[argc - 1])
		;
	store_env(env_tab, &env);
	while (42)
	{
		ft_printf("~ %s%s%s > ", COL_GRN, ft_strrchr(var_value(env, "PWD"), '/') + 1, COL_NRM);
		get_next_line(0, &line);
		if (ft_strstr(line, ";;"))
			ft_printf("zsh: parse error near `;;'\n");
		else
		{
			cmds = ft_split_set(line, ";");
			i = -1;
			while (cmds[++i])
			{
				cmd_tab = ft_split_set(cmds[i], " ");
				root(env, var_value(env, "PATH"), cmd_tab);
				free_str_tab(cmd_tab);
			}
			free_cmds(line, cmds);
		}
	}
	return (0);
}

/*
** TODO
** remove # include <stdio.h> in .h
** mettre free str tab dans libft
** ls $VAR ; ls ~
*/