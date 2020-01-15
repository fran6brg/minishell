/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisberger <francisberger@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/15 03:00:37 by francisberg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** global var for put_promt()
*/

t_env	*env;

/*
** root towards the right function
*/

void	root(t_env *env, char *path, char **cmd_tab)
{
	print_str_split(cmd_tab);
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
		if (count_arg(cmd_tab) > 2)
		{
			ft_printf("exit: too many arguments\n");
			exit(0);
		}
		exit(cmd_tab[1] ? ft_atoi(cmd_tab[1]) : 1); // exit 10 (la valeur 10 est retourné, 'echo $?' pour verifier dans ton "vrais" shell)
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

static void			put_prompt(void)
{
	ft_printf("~ %s%s%s > ", COL_GRN, ft_strrchr(var_value(env, "PWD"), '/') + 1, COL_NRM);
}

// https://stackoverflow.com/questions/7670816/create-extern-char-array-in-c

static void			nl_prompt(int signum)
{
	(void)signum;
	ft_putchar('\n');
	put_prompt();
}

static void			sigint_handler(void)
{
	signal(SIGINT, nl_prompt);
	signal(SIGQUIT, nl_prompt); // ctrl \
	// signal(?, nl_prompt); // ctrl D
}

int		main(int argc, char **argv, char **env_tab)
{
	char	*line;
	char	**cmds;
	char	**cmd_tab;
	int		i;
	
	if (argv[argc])
		;
	if (!store_env(env_tab, &env))
		return (0);
	while (42)
	{
		sigint_handler();
		put_prompt();
		if (!get_next_line(0, &line)) // if GNL ret 0 it means CTRL + D was hit which occurs EOF that quit shell
		{
			free_env(env);
			exit(0);
		}
		if (ft_strstr(line, ";;"))
			ft_printf("zsh: parse error near `;;'\n");
		else
		{
			cmds = ft_split_set(line, ";");
			i = -1;
			while (cmds[++i])
			{
				if (!(cmd_tab = ft_split_set_and_quotes(cmds[i], " \t"))) // tab egalement à virer
					continue ;
				root(env, var_value(env, "PATH"), cmd_tab);
				free_str_tab(cmd_tab);
			}
			free_cmds(line, cmds);
		}
	}
	return (1);
}

/*
** TODO
** remove # include <stdio.h> in .h
** mettre free str tab dans libft
** ls $VAR ; ls ~
** check headers
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/15 02:58:52 by francisberg 
*/