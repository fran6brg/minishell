/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 05:42:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/21 07:22:52 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** root towards the right function
**
** nb :
** else if (cmd_tab[0]) sert à protéger la fonction execute 
** contre la commande constituee d'une chaine d'espaces + enter
*/

void	root(char **cmd_tab)
{
	ft_print_str_tab(cmd_tab); // pour debug
	if (is_dollar_env_var(cmd_tab[0]))
		ft_printf("%s\n", var_value(cmd_tab[0] + 1));
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
	else if (cmd_tab[0])
		execute(cmd_tab);
}

/*
** real stuff happens here
*/

// void	connect_cmds(char **cmd_tab)
// {
//     int         pdes[2];
//     int	const   READ = 0;
// 	int	const	WRITE = 1;

//     replace_dollar_vars(cmd_tab);
//     if ()
//         ;
// }