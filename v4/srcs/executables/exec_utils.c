/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:04:17 by fberger           #+#    #+#             */
/*   Updated: 2020/01/25 22:11:48 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** get_left_exec_args();
*/

char **get_left_exec_args(char **cmd_tab)
{
    int     i;
    char    **left_args;

    i = 0;
    while (cmd_tab[i][0] != '|')
        i++;
    if (!(left_args = (char **)malloc(sizeof(char *) * (i + 1))))
        return (NULL);
    left_args[0] = NULL;
    left_args[i] = NULL;
    i = 0;
    while (cmd_tab[i][0] != '|')
    {
        if (i == 0)
        {
            if (is_builtin(cmd_tab))
                left_args[i] = ft_strdup(cmd_tab[i]);
            else
                check_paths(cmd_tab, left_args);
        }
        else
            left_args[i] = ft_strdup(cmd_tab[i]);
        i++;
    }
    return (left_args);
}


/*
** get_right_exec_args();
*/

char **get_right_exec_args(char **cmd_tab)
{
    int i;
    int j;
    char    **right_args;

    i = 0;
    while (cmd_tab[i][0] != '|')
        i++;
    i++;
    j = i;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
        j++;
    // ft_print_str_tab(cmd_tab + i, "INSIDE GREA\n");
    if (!(right_args = malloc(sizeof(char *) * (j - i + 1))))
        return (NULL);
    right_args[0] = NULL;
    right_args[j - i] = NULL;
    j = i;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
    {
        if (j == i)
        {
            if (is_builtin(cmd_tab + j))
                right_args[j - i] = ft_strdup(cmd_tab[j]);
            else
                check_paths(cmd_tab + j, right_args);
        }
        else
            right_args[j - i] = ft_strdup(cmd_tab[j]);
        j++;
    }
    return (right_args);
}

/*
** count_pipes();
*/

int		count_pipe(char **cmd_tab)
{
    int			i;
	int 		nb_pipe;

	i = 0;
    nb_pipe = 0;
    while (cmd_tab[i])
	{
		if (cmd_tab[i][0] == '|')
			nb_pipe++;
		i++;
	}
    return (nb_pipe);
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