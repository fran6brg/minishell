/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/02/07 08:44:48 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** store_env()
**
** store env inside global linked list g_env
*/

int		store_env(char **env_tab)
{
	int		i;
	t_env	*var;
	t_env	*last;
	int		len;

	i = -1;
	last = NULL;
	if (!env_tab || !*env_tab)
		return (0);
	while (env_tab[++i])
	{
		var = NULL;
		if (!(var = (t_env *)malloc(sizeof(t_env))))
			return (0);
		len = (int)(ft_strchr(env_tab[i], '=') - env_tab[i]);
		var->name = ft_substr(env_tab[i], 0, len);
		var->value = ft_substr(env_tab[i], len + 1, ft_strlen(env_tab[i]));
		var->next = NULL;
		if (last)
			last->next = var;
		else
			g_env = var;
		last = var;
	}
	return (1);
}

/*
** parse_and_root_cmds()
**
** 3 possibilités donc 3 if : pipeline || single builtin || single execv
*/

void	parse_and_root_cmds(char **cmds)
{
	int		i;
	char	**cmd_tab;

	i = -1;
	while (cmds[++i])
	{
		if (!(cmd_tab = ft_split_set_quotes_redirects(cmds[i])))
			continue ;
		replace_dollar_vars(cmd_tab);
		if (count_pipe(cmd_tab) > 0)
			run_pipeline(cmd_tab, 0);
		else if (cmd_is_builtin(cmd_tab))
			run_single_builtin(cmd_tab);
		else if (cmd_tab[0])
			run_single_execv(cmd_tab);
		ft_free_str_tab(cmd_tab);
	}
}

/*
** put_prompt()
**
** isolé ds une fonction pour pouvoir l'appeler depuis les fonctions SIG
** nb : ces fonctions ne prennent pas d'argument donc cela justifie
** le recours à une variable globale g_env pour pouvoir afficher le path
*/

void	put_prompt(void)
{
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	if ((tmp = var_value("$PWD")))
	{
		pwd = NULL;
		if ((pwd = ft_strrchr(tmp, '/') + 1))
			ft_printf("%s~ %s%s%s >%s ", BGREEN, BMAGENTA, pwd, BGREEN, RESET);
	}
	else
		ft_printf("%s~ %s%s%s >%s ", BGREEN, BMAGENTA, "bash", BGREEN, RESET);
}

/*
** main()
**
** listen_sig(); pour les CTRL + c || d || z
** put_prompt(); self-explained
** if (!get_next_line(STDIN_FILENO, &line) : if GNL ret 0 it means CTRL + D
** was hit which occurs EOF, that quits shell
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
	listen_sig();
	while (42)
	{
		*shell_is_running_cmd() = 0;
		put_prompt();
		if (!get_next_line(STDIN_FILENO, &line))
			free_and_exit(EXIT_FAILURE, NULL);
		else if (parse_error(line))
			;
		else
		{
			*shell_is_running_cmd() = 1;
			if (!(cmds = ft_split_cmds(line, ";")))
				continue ;
			parse_and_root_cmds(cmds);
			free_cmds(line, cmds);
		}
	}
	return (0);
}
