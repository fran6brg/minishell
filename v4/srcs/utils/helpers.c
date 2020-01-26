/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/26 04:56:07 by fberger          ###   ########.fr       */
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
** cmd_is_right_redirected()
*/

int	cmd_is_right_redirected(char **cmd_tab)
{
	int i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (!arg_is_in_quotes(cmd_tab[i]))
		{
			if (ft_strequ(cmd_tab[i], ">"))
				return (1);
			if (ft_strequ(cmd_tab[i], ">>"))
				return (1);
		}
		else if (cmd_tab[i][0] == '|')
			return (0);
	}
	return (0);
}

/*
** cmd_is_left_redirected()
*/

int	cmd_is_left_redirected(char **cmd_tab)
{
	int i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (!arg_is_in_quotes(cmd_tab[i]))
		{
			if (ft_strequ(cmd_tab[i], "<"))
				return (1);
		}
		else if (cmd_tab[i][0] == '|')
			return (0);
	}
	return (0);
}

/*
** contain_redirection();
*/

int		get_fd(char **args)
{
    int	i;
    int fd;

	i = 0;
	fd = -1;
    while (args[i])
	{
		if (args[i][0] == '>')
		{
			fd = open(args[i + 1], O_CREAT | O_WRONLY | (args[i][1] == '>' ? O_APPEND : O_TRUNC), 0777);
			return (fd);
        }
		i++;
	}
    return (fd);
}

/*
** is_builtin()
*/

int		is_builtin(char **cmd_tab)
{
	return (ft_strequ(cmd_tab[0], "echo")
	|| ft_strequ(cmd_tab[0], "cd")
	|| ft_strequ(cmd_tab[0], "pwd")
	|| ft_strequ(cmd_tab[0], "env")
	|| ft_strequ(cmd_tab[0], "setenv")
	|| ft_strequ(cmd_tab[0], "unset")
	|| ft_strequ(cmd_tab[0], "exit")
	);
}
