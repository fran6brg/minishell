/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:04:17 by fberger           #+#    #+#             */
/*   Updated: 2020/01/21 00:04:39 by fberger          ###   ########.fr       */
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
            check_paths(cmd_tab, left_args);
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
    j = ++i;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
        j++;
    if (!(right_args = malloc(sizeof(char *) * (j - i + 1))))
        return (NULL);
    right_args[0] = NULL;
    right_args[j - i] = NULL;
    j = i;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
    {
        if (j == i)
            check_paths(&cmd_tab[j], right_args);
        else
            right_args[j - i] = ft_strdup(cmd_tab[j]);
        j++;
    }
    return (right_args);
}