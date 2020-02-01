/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:17:50 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 05:11:25 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** nb_args_wo_offset()
** wo = without
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
** get_first_args();
** meaning before pipe if pipe
** here offset is used to skip '>' || '>>' || <filename> args
*/

char **get_first_args(char **cmd_tab)
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
		if (DEBUG)
			printf("inside first_args cmd_tab[%d] = %s\n", i, cmd_tab[i]);
        if (i == 0)
        {
            left_args[0] = NULL;
            if (cmd_is_builtin(cmd_tab))
                left_args[i] = ft_strdup(cmd_tab[i]);
            else
                find_exec_path(cmd_tab, left_args);
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
** get_second_args();
** meaning after pipe
** here offset is used to skip '>' || '>>' || <filename> args
*/

char **get_second_args(char **cmd_tab)
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
            else
                find_exec_path(cmd_tab + j, right_args);
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