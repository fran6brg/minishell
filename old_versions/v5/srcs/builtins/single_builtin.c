/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:55:13 by fberger           #+#    #+#             */
/*   Updated: 2020/02/04 09:29:00 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** cmd_is_builtin()
*/

int		cmd_is_builtin(char **cmd_tab)
{
	return ((is_env_var(cmd_tab[0])
	|| ft_strequci(cmd_tab[0], "echo")
	|| ft_strequci(cmd_tab[0], "cd")
	|| ft_strequci(cmd_tab[0], "pwd")
	|| ft_strequci(cmd_tab[0], "env")
	|| ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export")
	|| ft_strequci(cmd_tab[0], "unset")
	|| ft_strequci(cmd_tab[0], "exit")) ? 1 : 0);
}

/*
** reach_builtin_funct()
** root towards the right builtin function
**
** nb :
** else if (cmd_tab[0]) sert à protéger la fonction execute 
** contre la commande constituee d'une chaine d'espaces + enter
*/

int	reach_builtin_funct(char **cmd_tab)
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

/*
** run_single_builtin()
*/

int	run_single_builtin(char **cmd_tab)
{	
	int		fd;

	// if (DEBUG)
	// 	ft_print_str_tab(cmd_tab, "cmd_tab inside run_single_builtin"); // pour debug
	set_fd_for_single_cmd(cmd_tab, &fd);
	reach_builtin_funct(cmd_tab);
	restore_std_for_single_cmd(cmd_tab, &fd);
	return (1);
}
