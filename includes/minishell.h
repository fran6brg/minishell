/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:49:28 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 04:53:06 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

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
**	------------ main.c
*/

int		main(int argc, char **argv, char **env);

/*
**	------------ builtins/.c
*/

void	builtin_env(char **cmd_tab);
void	builtin_setenv(char **cmd_tab);
void	builtin_unsetenv(char **cmd_tab);
void	builtin_echo(char **cmd_tab);
void	builtin_cd(char **cmd_tab);

/*
**	------------ executables/.c
*/

void	exec(char **cmd_tab);

/*
**	------------ utils/.c
*/

void	print_env(t_env *env);
void    print_str_split(char **s);
void	free_cmds(char *cmd, char **cmd_tab);
void	free_env(t_env *env);

#endif
