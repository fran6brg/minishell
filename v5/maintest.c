/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 01:16:19 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/*
** good old main
*/

int		main(int argc, char **argv)
{
	char	*line;
	char	**cmds;

	(void)argv[argc];
	ft_printf("123%s789%d\n", "456", 101112);
	return (0);
}

/*
** TODO
** remove # include <stdio.h> in .h
** valider le comportemenet ctrl bl
** ls -la | cat -e | env
** ls -la | cat -e | sort > filename
*/