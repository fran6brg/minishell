/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/18 23:10:54 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** root towards the right function
*/

void	root(char *path, char **cmd_tab)
{
	// ft_print_str_tab(cmd_tab);
	if (is_dollar_env_var(cmd_tab[0])) // $VAR
		ft_printf("%s\n", var_value(cmd_tab[0] + 1));
	else if (ft_strequci(cmd_tab[0], "echo"))
		builtin_echo(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "cd"))
		builtin_cd(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "pwd"))
		builtin_pwd();
	else if (ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export"))
		builtin_setenv(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "unset"))
		builtin_unsetenv(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "env"))
		builtin_env();
	else if (ft_strequci(cmd_tab[0], "exit"))
	{
		if (count_arg(cmd_tab) > 2)
			free_and_exit(0, "exit: too many arguments\n");
		free_and_exit(cmd_tab[1] ? ft_atoi(cmd_tab[1]) : 1, NULL); // exit 10 (la valeur 10 est retournée, 'echo $?' pour verifier dans le "vrai" shell)
	}
	else if (cmd_tab[0]) // pour protéger contre la commande constituee d'une chaine d'espaces + enter
		execute(cmd_tab, path);
}


void	parse_and_root_cmds(char **cmds)
{
	int		i;
	char	**cmd_tab;

	i = -1;
	while (cmds[++i])
	{
		if (!(cmd_tab = ft_split_set_quotes_chevrons(cmds[i], " \t")))
			continue ;
		root(var_value("PATH"), cmd_tab);
		free_str_tab(cmd_tab);
	}
}

/*
** put prompt isolé pour pouvoir l'appeler depuis les fonctions de gestion des sig
*/

void			put_prompt(void)
{
	ft_printf("~ %s%s%s > ", COL_GRN, ft_strrchr(var_value("PWD"), '/') + 1, COL_NRM);
}

int		main(int argc, char **argv, char **env_tab)
{
	char	*line;
	char	**cmds;

	(void)argv[argc];
	if (!store_env(env_tab))
		return (0);
	while (42)
	{
		sigint_handler();
		put_prompt();
		if (!get_next_line(STDIN_FILENO, &line)) // if GNL ret 0 it means CTRL + D was hit which occurs EOF, that quits shell
			free_and_exit(0, NULL);
		if (parse_error(line))
			free_and_exit(0, NULL);
		else
		{
			if (!(cmds = ft_split_set(line, ";")))
				continue ;
			parse_and_root_cmds(cmds);
			free_cmds(line, cmds);
		}
	}
	return (1);
}

/*
** TODO
** remove # include <stdio.h> in .h
** ls $VAR ; ls ~
** valider le comportemenet ctrl bl
** echo "lol\'"> a 123 456
*/