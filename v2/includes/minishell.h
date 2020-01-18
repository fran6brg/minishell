/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:49:28 by fberger           #+#    #+#             */
/*   Updated: 2020/01/18 04:11:35 by fberger          ###   ########.fr       */
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
# include <signal.h>

/*
**	structs
*/

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct	s_env	*next;
}					t_env;

// extern t_env	*env;

/*
**	main.c
*/

void	root(t_env *env, char *path, char **cmd_tab);
void	put_prompt(void);
void	parse_and_root_cmds(t_env *env, char **cmds);
int		main(int argc, char **argv, char **env);

/*
**	echo.c
*/

int		is_$env_var(t_env *env, char *var);
void	apply_redirect(t_env *env, char **cmd_tab, int pos);
void	builtin_echo(t_env *env, char **cmd_tab);

/*
**	cd.c
*/

int		change_dir(t_env *env, char **cmd_tab, char *dest);
void	go_home(t_env *env, char *home, char **cmd_tab);
void	go_path(t_env *env, char **cmd_tab);
void	print_cd_error(int nb_arg, char **cmd_tab);
void	builtin_cd(t_env *env, char **cmd_tab);

/*
**	pwd.c
*/

void	builtin_pwd(t_env *env);

/*
**	env.c
*/

char	*var_value(t_env *env, char *name);
int		store_env(char **env_tab, t_env **env);
int		is_env_var(t_env *env, char *arg);
void	builtin_env(t_env *env);
void	builtin_unsetenv(char **cmds, t_env *env);
void	builtin_setenv(char **cmds, t_env *env);

/*
**	exec.c
*/

int		execute(char **cmd_tab, char *path);

/*
**	utils.c
*/

void    print_str_split(char **s);
int		count_arg(char **s);
int		arg_is_in_quotes(char *arg);

/*
**	split_1.c
*/

int		is_separator(char c, char *set);
char	**ft_split_set_quotes_chevrons(char const *s, char *set);
int		ft_new_str_with_quotes(const char *s, char *quote, char **strs, int *str_i);
int		ft_new_str_chevron(const char *s, char *quote, char **strs, int *str_i);
int		ft_new_str(const char *s, char *set, char **strs, int *str_i);

/*
**	split_2.c
*/

int		nb_new_s(char const *s, char *set);

/*
**	split_3.c
*/

int		ft_str_with_quotes(const char *s, int *i, char **strs, int *str_i);
int		ft_str_with_chevron(const char *s, int *i, char **strs, int *str_i, char *set);
int		ft_create_strs(char **strs, const char *s, int *str_i, char *set);

/*
**	errors.c
*/

int		parse_error(char *line);
int		multilines(const char *s);

/*
**	free.c
*/

void	free_str_tab(char **str_tab);
void	free_cmds(char *line, char **cmds);
void	free_env(t_env *env);
void	free_and_exit(t_env *env, int exit_value, char *msg);

/*
**	signal.c
*/

void	sigint_handler(void);

#endif
