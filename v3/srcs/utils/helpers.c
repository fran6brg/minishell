/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/20 04:10:48 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** count_arg
*/

int    count_arg(char **s)
{
    int i;

    i = 0;
    while (s[++i])
		;
	return (i);
}

/*
** arg_is_in_quotes()
*/

int arg_is_in_quotes(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	return (((arg[0] == '\'' || arg[0] == '"') && (arg[len - 1] == '\'' || arg[len - 1] == '"')));
}

/*
** check_if_redirect()
*/

int	check_if_redirect(char **cmd_tab)
{
	int i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (!arg_is_in_quotes(cmd_tab[i]))
		{
			if (ft_strequ(cmd_tab[i], "<"))
				return (1);
			if (ft_strequ(cmd_tab[i], ">"))
				return (2);
			if (ft_strequ(cmd_tab[i], ">>"))
				return (3);
		}
	}
	return (0);
}

/*
** cmd_contains_pipe()
*/

int		cmd_contains_pipe(char **cmd_tab)
{
	int i;

    i = 0;
    while (cmd_tab[++i])
	{
		if (cmd_tab[i][0] == '|')
			return (1);
	}
	return (0);
}
