/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 23:38:52 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:08 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** replace_by_status()
*/

int		replace_by_status(char **cmd_tab, int i)
{
	if (ft_strequ(cmd_tab[i], "$?"))
	{
		ft_strdel(&cmd_tab[i]);
		cmd_tab[i] = ft_strdup(ft_itoa(*get_exit_status()));
		return (1);
	}
	return (0);
}

/*
** get_exit_status()
*/

int		*get_exit_status(void)
{
	static int status;

	return (&status);
}

/*
** exit()
** si cmd_tab = [exit; 10] la valeur 10 est retournée
** 'echo $?' pour verifier ce retour dans le vrai shell
*/

void	exit_minishell(char **cmd_tab)
{
	ft_printf("exit\n");
	if (count_arg(cmd_tab) > 2)
		free_and_exit(EXIT_FAILURE, "exit: too many arguments\n");
	free_and_exit(cmd_tab[1] ? ft_atoi(cmd_tab[1]) : EXIT_SUCCESS, NULL);
}
