/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:42:37 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 06:29:57 by fberger          ###   ########.fr       */
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
** right_redirected_cmd()
*/

int	right_redirected_cmd(char **cmd_tab)
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
** left_redirected_cmd()
*/

int	left_redirected_cmd(char **cmd_tab)
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
** get_fd();
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
		else if (args[i][0] == '<')
		{
			fd = open(args[i + 1], O_CREAT | O_WRONLY, 0777);
			return (fd);
        }
		i++;
	}
    return (-1);
}
