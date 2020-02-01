/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:17:50 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 05:58:37 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** nb_args_wo_offset()
**
** '_wo_' == without
*/

int		nb_args_wo_offset(char **cmd_tab)
{
	int		i;
	int		offset;

	i = 0;
	offset = 0;
	while (cmd_tab[i] && cmd_tab[i][0] != '|')
    {
		if (ft_strchr("<>", cmd_tab[i][0]) || (i > 0 && ft_strchr("<>", cmd_tab[i - 1][0])))
			offset++;
        i++;
    }
	if (DEBUG)
		printf("nb_args_wo_offset = %d\n", i - offset);
	return (i - offset);
}

/*
** format_args();
**
** get args before pipe if pipe : args | args_after_pipe
** here offset is used to skip '>' || '>>' || <filename> args
*/

char **format_args(char **cmd_tab)
{
    int     i;
    char    **left_args;
	int		offset;

	i = nb_args_wo_offset(cmd_tab);
    if (!(left_args = malloc(sizeof(char *) * (i + 1))))
        return (NULL);
    left_args[i] = NULL;
    i = 0;
	offset = 0;
    while (cmd_tab[i] && cmd_tab[i][0] != '|')
    {
        if (i == 0)
        {
            if (DEBUG)
                printf("inside i == 0 | find_exec_path(cmd_tab, left_args) = %d\n", find_exec_path(cmd_tab, left_args));
            left_args[0] = NULL;
            if (cmd_is_builtin(cmd_tab))
                left_args[i] = ft_strdup(cmd_tab[i]);
            else if (!find_exec_path(cmd_tab, left_args))
                return (NULL);
        }
		else if (ft_strchr("<>", cmd_tab[i][0]) || ft_strchr("<>", cmd_tab[i - 1][0]))
			offset++;
        else
            left_args[i - offset] = ft_strdup(cmd_tab[i]);
        i++;
    }
	if (DEBUG)
		ft_print_str_tab(left_args, "inside first_args");
    return (left_args);
}

/*
** format_args_after_pipe();
**
** get args after pipe : args_before_pipe | args
** here offset is used to skip '>' || '>>' || <filename> args
*/

char **format_args_after_pipe(char **cmd_tab)
{
    int 	i;
    int 	j;
    char    **right_args;
	int		offset;

    i = next_pipe_pos_or_len(cmd_tab) + 1;
    j = i + nb_args_wo_offset(cmd_tab + i);
    if (!(right_args = malloc(sizeof(char *) * (j - i + 1))))
        return (NULL);
    right_args[j - i] = NULL;
    j = i;
	offset = 0;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
    {
        if (j == i)
        {
            right_args[0] = NULL;
            if (cmd_is_builtin(cmd_tab + j))
                right_args[j - i] = ft_strdup(cmd_tab[j]);
            else if (!find_exec_path(cmd_tab + j, right_args))
                return (NULL);
        }
		else if (ft_strchr("<>", cmd_tab[j][0]) || ft_strchr("<>", cmd_tab[j - 1][0]))
			offset++;
        else
            right_args[j - i - offset] = ft_strdup(cmd_tab[j]);
        j++;
    }
	if (DEBUG)
		ft_print_str_tab(right_args, "inside second_args");
    return (right_args);
}