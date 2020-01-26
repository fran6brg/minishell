/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 23:38:52 by fberger           #+#    #+#             */
/*   Updated: 2020/01/26 01:18:12 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** exit()
** si cmd_tab = [exit; 10] la valeur 10 est retournée
** 'echo $?' pour verifier ce retour dans le vrai shell
*/

void	exit_minishell(char **cmd_tab)
{
	if (count_arg(cmd_tab) > 2)
		free_and_exit(0, "exit: too many arguments\n");
	free_and_exit(cmd_tab[1] ? ft_atoi(cmd_tab[1]) : EXIT_SUCCESS, NULL);
}
