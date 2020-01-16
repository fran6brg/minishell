/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:48:45 by fberger           #+#    #+#             */
/*   Updated: 2020/01/16 04:56:35 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		parse_error(char *line)
{
    if (ft_strstr(line, ";;"))
    {
        ft_printf("zsh: parse error near `;;'\n");
        return (1);
    }
    else if (ft_strstr(line, ">>>"))
    {
        ft_printf("zsh: parse error near `>'\n");
        return (1);
    }
    else if (ft_strstr(line, "<<<")) // "<<"" = bonus
    {
        ft_printf("zsh: parse error near `<'\n");
        return (1);
    }
    else
        return (0);
}