/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:49:28 by fberger           #+#    #+#             */
/*   Updated: 2020/01/21 02:52:02 by fberger          ###   ########.fr       */
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

extern t_env *g_env;

/*
** ----------------------------------------------------------------------------
*/

/*
**	main.c
*/

int		store_env(char **env_tab);
void	root(char **cmd_tab);
void	parse_and_root_cmds(char **cmds);
void	put_prompt(void);
int		main(int argc, char **argv, char **env);

/*
** ----------------------------------------------------------------------------
*/

/*
**	echo.c
*/

int		store_filename(char **filename, char **cmd_tab, int pos);
int		parse_filename(char **cmd_tab, char **filename, int *fd);
void	apply_redirect_right(char **cmd_tab);
void	builtin_echo(char **cmd_tab);

/*
**	echo_utils.c
*/

int		is_n_option(int i, char **cmd_tab);
int		no_option_n(char **cmd_tab);

/*
**	cd.c
*/

int		change_dir(char **cmd_tab, char *dest);
void	go_path(char **cmd_tab, char *dest);
void	print_cd_error(int nb_arg, char **cmd_tab);
void	get_destination(char **cmd_tab, char **dest);
void	builtin_cd(char **cmd_tab);

/*
**	pwd.c
*/

void	builtin_pwd();

/*
**	env.c
*/

char	*var_value(char *name);
void	builtin_env();
void	builtin_unsetenv(char **cmds);
int		builtin_setenv(char **cmds);
void	builtins_env(char **cmds);

/*
**	env_utils.c
*/

int		is_env_var(char *arg);
int		is_dollar_env_var(char *var);
void	replace_dollar_vars(char **cmd_tab);

/*
**	exit.c
*/

void	exit_minishell(char **cmd_tab);

/*
** ----------------------------------------------------------------------------
*/

/*
**	exec.c
*/

int		check_direct_path_to_exec(char *tested_path, struct stat *s);
int		check_paths(char **cmd_tab, char **exec_path);
int		fork_and_exec(char **cmd_tab, char *exec_path);
int		handle_pipe(char **cmd_tab, int recursive_call);
int		execute(char **cmd_tab);

/*
**	exec_utils.c
*/

char	**get_left_exec_args(char **cmd_tab);
char	**get_right_exec_args(char **cmd_tab);

/*
** ----------------------------------------------------------------------------
*/

/*
**	split_1.c
*/

int		is_separator(char c, char *set);
char	**ft_split_set_quotes_chevrons(char *s, char *set);
int		ft_new_str_with_quotes(char *s, char *quote, char **strs, int *str_i);
int		ft_new_str_chevron(char *s, char *quote, char **strs, int *str_i);
int		ft_new_str(char *s, char *set, char **strs, int *str_i);
int		ft_str_pipe(char **strs, int *str_i);

/*
**	split_2.c
*/

void	ft_inc_to_closing_quote(int *i, char *s);
int		nb_new_s(char *s, char *set);

/*
**	split_3.c
*/

int		ft_str_with_quotes(char *s, int *i, char **strs, int *str_i);
int		ft_str_with_chevron(char *s, int *i, char **strs, int *str_i, char *set);
int		ft_create_strs(char *s, char **strs, int *str_i, char *set);

/*
**	errors.c
*/

int		parse_error(char *line);
int		multilines(char *s, char *set);

/*
**	signal.c
*/

void	handle_sig(void);

/*
**	helpers.c
*/

int		count_arg(char **s);
int		arg_is_in_quotes(char *arg);
int		check_if_redirect(char **cmd_tab);
int		cmd_contains_pipe(char **cmd_tab);

/*
**	free.c
*/

void	free_cmds(char *line, char **cmds);
void	free_env();
void	free_and_exit(int exit_value, char *msg);

#endif
