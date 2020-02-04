/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/02/04 14:16:54 by fberger          ###   ########.fr       */
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
	if (!env_tab || !*env_tab) // env -i
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
		if (!(cmd_tab = ft_split_set_quotes_chevrons(cmds[i], " \t")))
			continue ;
		if (DEBUG)
			ft_print_str_tab(cmd_tab, "parse_and_root_cmds"); // pour debug
		replace_dollar_vars(cmd_tab);
		if (count_pipe(cmd_tab) > 0)
			run_pipeline(cmd_tab, 0);
		else if (cmd_is_builtin(cmd_tab))
			run_single_builtin(cmd_tab);
		else if (cmd_tab[0]) // meaning if at leat 1 arg
			run_single_execv(cmd_tab);
		ft_free_str_tab(cmd_tab);
	}
}

/*
** put_prompt()
**
** isolé ds une fonction pour pouvoir l'appeler depuis les fonctions de gestion des SIG
** nb : ces fonctions de gestion des SIG ne prennent pas d'argument donc cela justifie
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
	while (42)
	{
		listen_sig();
		put_prompt();
		if (!get_next_line(STDIN_FILENO, &line) || parse_error(line))
			free_and_exit(EXIT_FAILURE, NULL);
		else
		{
			if (!(cmds = ft_split_cmds(line, ";")))
				continue ;
			if (DEBUG)
				ft_print_str_tab(cmds, "main"); // pour debug
			parse_and_root_cmds(cmds);
			free_cmds(line, cmds);
		}
	}
	return (0);
}

/*
** TODO :

** remove # include <stdio.h> in .h

** comprendre le pb 'Uninitialised value was created by a heap allocation' avec 'make re && valgrind --leak-check=full --track-origins=yes ./minishell'

** norme

** est-ce que le echo < filename (left redirection) existe/est à faire ?

** protection des mallocs ?

** mettre certaines fonctions en static pour la forme

** cleaner split_cmds.c (fonctionnel mais code pas super propre), renommer les fonctions de facon explicite / repenser le code etc

** compiler avec -fsanitize=address (attention ne pas combiner fsanitize avec valgrind sinon bug)

** regler les pb de 'valgrind --leak-check=full --track-origins=yes ./minishell'

** si on lance ./minishell dans ./minishell il faut que le second ait bien les variables d'env du premier ?

** lister tous les tests qui passent / passent pas, en attendant d'avoir le sujet d'exam

** handle errors ">>>"

** ** SIGQUIT ctrl backslash -> todo : quit without displaying new prompt (right behaviour)

** ft_printf("minishell: command not found : %s\n", cmd_tab[0]); trop restrictif

**echo > | | salut ; | ;
**bash: syntax error near unexpected token `|'

** ls | ./minishell

** echo "lol;;"

*/