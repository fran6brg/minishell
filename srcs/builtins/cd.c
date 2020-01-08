/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:22 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 05:00:52 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_cd(char **cmd_tab)
{
    // print_str_split(cmd_tab);
	int i;

	i = -1;
	while (cmd_tab[++i])
		;
	if (!cmd_tab[1] || (cmd_tab[1] != 0 && !ft_strncmp(cmd_tab[1], "~", 1)))
		go_home(list_env, get_env_var(list_env, "HOME"), cmd_tab);
	if (i == 3)
		ft_printf("cd: string not in pwd: %s\n", cmd_tab[1]);
	else if (i > 3)
		ft_printf("cd: too many arguments\n");
	/* Le if qui suit intervient pour gérer le cas "cd" (sans args) ou "cd ~" */
	else
		move_to_path(list_env, cmd_tab);
}
