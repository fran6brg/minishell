/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/11 04:44:58 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** root towards the right function
*/

void	root(t_env *env, char *path, char **cmd_tab)
{
	// print_str_split(cmd_tab);
	if (ft_strequci(cmd_tab[0], "echo"))
		builtin_echo(cmd_tab);
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
	else
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

// int		ft_split_cmd_tab(char **cmd_tab)
// {
// 	int		i;
// 	int		j;
// 	int		semicolon;
// 	int		k;
// 	int		l;
// 	char	***cmd_tabs;
// 	char	**tmp;

// 	i = -1;
// 	semicolon = 0;
// 	while (cmd_tab[++i])
// 	{
// 		j = -1;
// 		while (cmd_tab[i][++j])
// 		{
// 			if (cmd_tab[i][j] == ';')
// 					semicolon += 1;
// 		}
// 	}
// 	if (semicolon >= 1)
// 	{
// 		cmd_tabs = malloc(sizeof(char **) * (semicolon + 1 + 1));
// 		k = -1;
// 		while (++k < semicolon + 1)
// 		{
// 			i = -1;
// 			while (cmd_tab[i][++j])
// 			{
// 				if (cmd_tab[i][j] == ';')
// 				{
// 					cmd_tabs[k] = malloc(sizeof(char **) * (i + 1 + (ft_str_end_with(cmd_tab[j], ";") ? 0 : 1) + 1));
// 					l = -1;
// 					while (++l < i - 1)
// 					{
// 						cmd_tabs[k][l] = ft_strdup(cmd_tab[l]);
// 					}
// 					if ((int)(ft_strrchr(cmd_tab[l], ';') - cmd_tab[l][0]) == 0)
// 					{
// 						cmd_tabs[k][l] = ft_strdup(";");
// 					}
// 					else
// 						cmd_tabs[k][l] = ft_substr(cmd_tab[l], 0, (int)(ft_strrchr(cmd_tab[l], ';') - cmd_tab[l][0]));
// 					if (!ft_str_end_with(cmd_tab[l], ";"))
// 						cmd_tabs[k][++l] = ft_substr(cmd_tab[l], (int)(ft_strrchr(cmd_tab[l], ';') - cmd_tab[l][0]), ft_strlen(cmd_tab[l]));
// 				}
// 			}
// 			cmd_tabs[k + 1] = 0;
// 		}
// 	}
// }

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
	
  	(void)argc;
  	(void)argv;
	env = NULL;
	store_env(env_tab, &env);
	while (1)
	{
		ft_printf("~ %s > ", ft_strrchr(var_value(env, "PWD"), '/') + 1);
		get_next_line(0, &line);
		if (ft_strstr(line, ";;"))
			ft_printf("zsh: parse error near `;;'\n");
		else
		{
			cmds = ft_split_set(line, ";");
			// print_str_split(cmds);
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
** s'assuer que ft_printf("~ %s > ", ft_strrchr(var_value(env, "PWD"), '/') + 1); work at home
** remove # include <stdio.h> in .h
** free str tab dans libft
*/