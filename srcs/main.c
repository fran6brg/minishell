/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/15 20:09:34 by fberger          ###   ########.fr       */
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
	if (is_$env_var(env, cmd_tab[0])) // $VAR
		write(1, "\n", 1);
	else if (ft_strequci(cmd_tab[0], "echo"))
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
		if (count_arg(cmd_tab) > 2)
			free_and_exit(env, 0, "exit: too many arguments\n");
		free_and_exit(env, cmd_tab[1] ? ft_atoi(cmd_tab[1]) : 1, NULL); // exit 10 (la valeur 10 est retourné, 'echo $?' pour verifier dans ton "vrais" shell)
	}
	else if (cmd_tab[0]) // pour protéger contre la commande chaine d'espaces + enter
		execute(cmd_tab, path);
}


void	parse_and_root_cmds(t_env *env, char **cmds)
{
	int		i;
	char	**cmd_tab;

	i = -1;
	while (cmds[++i])
	{
		if (!(cmd_tab = ft_split_set_and_quotes(cmds[i], " \t")))
			continue ;
		root(env, var_value(env, "PATH"), cmd_tab);
		free_str_tab(cmd_tab);
	}
}

/*
** 3e argument de la fonction main == l’ensemble des variables d’environment
*/

void			put_prompt(void)
{
	ft_printf("~ %s%s%s > ", COL_GRN, ft_strrchr(var_value(env, "PWD"), '/') + 1, COL_NRM);
}

int		main(int argc, char **argv, char **env_tab)
{
	char	*line;
	char	**cmds;
	
	(void)argv[argc];
	if (!store_env(env_tab, &env))
		return (0);
	while (42)
	{
		sigint_handler();
		put_prompt();
		if (!get_next_line(STDIN_FILENO, &line)) // if GNL ret 0 it means CTRL + D was hit which occurs EOF that quit shell
			free_and_exit(env, 0, NULL);
		if (ft_strstr(line, ";;"))
			ft_printf("zsh: parse error near `;;'\n");
		else
		{
			cmds = ft_split_set(line, ";");
			parse_and_root_cmds(env, cmds);
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
**   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             
**   Updated: 2020/01/15 02:58:52 by francisberg 
** valider le comportemenet ctrl bl
*/