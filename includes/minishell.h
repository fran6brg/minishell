/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:49:28 by fberger           #+#    #+#             */
/*   Updated: 2020/01/07 19:38:50 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define	MINISHELL_H

# include "libft.h"
/*
**	http://manpagesfr.free.fr/man/man2/wait.2.html
*/

# include <sys/types.h>
# include <sys/stat.h>

/*
**	to	futher	remove
*/

# include <stdio.h>

/*
**	structs
*/

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct	s_env	*next;
}					t_env;

/*
**	------------ main.c         ------------
*/

int	main(int argc, char **argv, char **env);

/*
**	------------ builtins/.c    ------------
*/


/*
**	------------ executables/.c ------------
*/

#endif
