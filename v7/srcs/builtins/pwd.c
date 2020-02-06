/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 00:36:06 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 11:51:31 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** builtin_pwd()
*/

void	builtin_pwd(void)
{
	if (var_value("$PWD"))
		ft_printf("%s\n", var_value("$PWD"));
	*get_exit_status() = EXIT_SUCCESS;;		
}
