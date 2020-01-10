/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:49:28 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 21:28:30 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

/*
**	http://manpagesfr.free.fr/man/man2/wait.2.html
*/

# include <sys/types.h>
# include <sys/stat.h>
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
**	main.c
*/

void	root(t_env *env, char *path, char **cmd_tab);
char	*var_value(t_env *env, char *name);
int		store_env(char **env_tab, t_env **env);
int		main(int argc, char **argv, char **env);

/*
**	echo.c
*/

void	builtin_echo(char **cmd_tab);

/*
**	cd.c
*/

int		change_dir(char **cmd_tab, char *dest);
void	go_home(t_env *env, char *home, char **cmd_tab);
void	go_path(t_env *env, char **cmd_tab);
void	builtin_cd(t_env *env, char **cmd_tab);

/*
**	pwd.c
*/

void	builtin_pwd(t_env *env);

/*
**	env.c
*/

void	builtin_env(t_env *env);
void	builtin_unsetenv(char **cmds, t_env *env);
void	builtin_setenv(char **cmds, t_env *env);

/*
**	exec.c
*/

void	exec(char **cmd_tab, char *path);

/*
**	free.c
*/

void    print_str_split(char **s);
int		nb_arg(char **s);

/*
**	free.c
*/

void	free_cmds(char *cmd, char **cmd_tab);
void	free_env(t_env *env);

#endif
