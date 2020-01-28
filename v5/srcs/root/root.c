/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 05:42:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/28 04:57:43 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** single_builtin()
** root towards the right builtin function
**
** nb :
** else if (cmd_tab[0]) sert à protéger la fonction execute 
** contre la commande constituee d'une chaine d'espaces + enter
*/

int	single_builtin(char **cmd_tab)
{
	if (is_env_var(cmd_tab[0]))
		ft_printf("%s\n", var_value(cmd_tab[0]));
	else if (ft_strequci(cmd_tab[0], "echo"))
		builtin_echo(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "cd"))
		builtin_cd(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "pwd"))
		builtin_pwd();
	else if (ft_strequci(cmd_tab[0], "env")
	|| ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export")
	|| ft_strequci(cmd_tab[0], "unset"))
		builtins_env(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "exit"))
		exit_minishell(cmd_tab);
	return (1);
}

void	single_execv(char **cmd_tab)
{
	char	**formated_args;
	pid_t   child;
	int		status;
	int		fd;

	replace_dollar_vars(cmd_tab);
	status = 0;
	if ((formated_args = get_first_args(cmd_tab)))
	{
		if (DEBUG)
			ft_print_str_tab(formated_args, "one shot execv"); // pour debug
		child = fork();
		if (child == -1) // 1.err
			exit(EXIT_FAILURE);
		else if (child == 0) // 2.fils
		{
			fd = get_fd(cmd_tab);
			if (fd != -1 && right_redirected_cmd(cmd_tab))
				dup2(fd, STDOUT_FILENO);
			else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
				dup2(fd, STDIN_FILENO);
			exit((execv(formated_args[0], formated_args) == -1) ? EXIT_FAILURE : EXIT_SUCCESS);
			close((fd && fd != -1) ? fd : -1);
			ft_free_str_tab(formated_args);
		}
		else // 3. parent
		{
			waitpid(child, &status, 0);
			ft_free_str_tab(formated_args);
		}
	}
}

/*
** is_builtin()
*/

int		is_builtin(char **cmd_tab)
{
	return (/* ft_strequci(cmd_tab[0], "echo")
	|| */ ft_strequci(cmd_tab[0], "cd")
	|| ft_strequci(cmd_tab[0], "pwd")
	|| ft_strequci(cmd_tab[0], "env")
	|| ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "unset")
	|| ft_strequci(cmd_tab[0], "exit")
	|| is_env_var(cmd_tab[0])
	);
}

/*
** root_args
*/

int	root_args(char **cmd_tab)
{
	if (DEBUG)
		ft_print_str_tab(cmd_tab, "inside root args"); // pour debug
	if (is_builtin(cmd_tab))
	{
		if (!single_builtin(cmd_tab))
			return (1);
	}
	else
	{
		if (execv(cmd_tab[0], cmd_tab) == -1)
			return (1);
	}
	return (0);
}
