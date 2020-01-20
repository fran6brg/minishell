/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:04:17 by fberger           #+#    #+#             */
/*   Updated: 2020/01/20 07:28:17 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** get_exec_args();
*/

int get_exec_args(char **cmd_tab, char ***left_args, char ***right_args)
{
    int i;
    int j;

    i = 0;
    while (cmd_tab[i][0] != '|')
        i++;
    *left_args = (char **)malloc(sizeof(char *) * i);
    printf("ok malloc\n");
    i = 0;
    while (cmd_tab[i][0] != '|')
    {
        printf("cmd_tab[i] = %s\n", cmd_tab[i]);
        if (i == 0)
        {
            // *left_args = NULL;
            check_paths(cmd_tab, *left_args);
            printf("cmd_tab[i] = %s\n", cmd_tab[i]);
        }
        else
            *left_args[i] = ft_strdup(cmd_tab[i]);
        printf("*left_args[i] = %s\n", *left_args[i]);
        i++;
    }
    i++;
    j = i;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
        j++;
    *right_args = malloc(sizeof(char *) * (j - i));
    j = i;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
    {
        printf("cmd_tab[j] = %s\n", cmd_tab[i]);
        if (j == i)
        {
            *right_args = NULL;
            check_paths(cmd_tab + j, *right_args);
        }
        else
            *right_args[j] = ft_strdup(cmd_tab[j]);
        printf("*right_args[j] = %s\n", *right_args[j]);
        j++;
    }
    return (1);
}