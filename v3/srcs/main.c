/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/22 01:13:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** store env inside list
*/

int		store_env(char **env_tab)
{
	int		i;
	t_env	*var;
	t_env	*last;
	
	i = -1;
	last = NULL;
	if (!env_tab || !*env_tab) // env -i
		return (0);
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
			g_env = var;
		last = var;
	}
	return (1);
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
		root(cmd_tab);
		ft_free_str_tab(cmd_tab);
	}
}

/*
** put prompt isolé pour pouvoir l'appeler depuis les fonctions de gestion des sig
*/

void	put_prompt(void)
{
	ft_printf("~ %s%s%s > ", COL_GRN, ft_strrchr(var_value("PWD"), '/') + 1, COL_NRM);
}

/*
** good old main
*/

int		main(int argc, char **argv, char **env_tab)
{
	char	*line;
	char	**cmds;

	if (argc != 1)
		return (0);
	(void)argv[argc];
	if (!store_env(env_tab))
		return (0);
	while (42)
	{
		handle_sig();
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
** cat -e abc
** cd ~Desktop
*/