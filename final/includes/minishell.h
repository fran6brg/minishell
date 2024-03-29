/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:49:28 by fberger           #+#    #+#             */
/*   Updated: 2020/02/11 17:04:24 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

/*
**	CONSTANTES
*/

# define READ	0
# define WRITE	1

/*
**	structs
*/

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

extern t_env	*g_env;

/*
** srcs/. ---------------------------------------------------------------------
*/

/*
**	main.c
*/

int					store_env(char **env_tab);
void				parse_and_root_cmds(char **cmds);
void				put_prompt(void);
int					main(int argc, char **argv, char **env);

/*
** srcs/builtins/. ------------------------------------------------------------
*/

/*
**	single_builtin.c
*/

int					cmd_is_builtin(char **cmd_tab);
int					reach_builtin_funct(char **cmd_tab);
int					run_single_builtin(char **cmd_tab);

/*
**	echo.c
*/

int					store_filename(char **filename, char **cmd_tab, int pos);
int					parse_filename(char **cmd_tab, char **filename, int *fd);
void				apply_redirect_right(char **cmd_tab);
void				builtin_echo(char **cmd_tab);

/*
**	echo_utils.c
*/

int					is_n_option(int i, char **cmd_tab);
int					no_option_n(char **cmd_tab);

/*
**	cd.c
*/

int					change_dir(char **cmd_tab, char *dest);
void				go_path(char **cmd_tab, char *dest);
void				print_cd_error(int nb_arg, char **cmd_tab);
void				get_destination(char **cmd_tab, char **dest);
void				builtin_cd(char **cmd_tab);

/*
**	pwd.c
*/

void				builtin_pwd();

/*
**	env.c
*/

char				*var_value(char *name);
void				builtin_env();
void				builtin_unsetenv(char **cmds);
void				builtin_export(char **cmds);
void				builtins_env(char **cmds);

/*
**	env_utils_1.c
*/

int					is_env_var(char *var);
void				replace_dollar_vars(char **cmd_tab);
int					is_dollar_env_var(char *var);
void				push_back_var(char *name, char *value);
void				remove_var(char *arg);

/*
**	env_utils_2.c
*/

void				parse_name_and_value(char *arg, char **name, char **value);
void				swap_sprite_data(t_env *var_j, t_env *var_j_next);
void				sort_env_var(void);
void				display_declared_vars(int i);

/*
**	exit.c
*/

int					replace_by_status(char **cmd_tab, int i);
int					*last_cmd_exit(void);
void				exit_minishell(char **cmd_tab);

/*
** srcs/exec/. ----------------------------------------------------------------
*/

/*
**	single_execv.c
*/

void				waitpid_and_free_args(pid_t child, int tube[2],
					int right_side, char **args);
void				run_single_execv(char **cmd_tab);

/*
**	path.c
*/

int					path_to_exec_is_valid(char *tested_path);
int					command_not_found_ret(char **cmd_tab, int printnotfound);
int					find_exec_path(char **cmd_tab, char **exec_path,
					int printnotfound);

/*
**	exec_utils.c
*/

int					next_pipe_pos_or_len(char **cmd_tab);
int					count_pipe(char **cmd_tab);
int					exit_process(int tube[2]);

/*
** srcs/pipeline/. ------------------------------------------------------------
*/

/*
**	pipeline.c
*/

int					run_builtin_or_execv(char **cmd_tab);
void				fork_left_cmd(char **cmd_tab, int tube[2],
					char **left_args);
void				fork_right_cmd(char **cmd_tab, int tube[2],
					char **right_args, int recursive_call);
int					run_pipeline(char **cmd_tab, int recursive_call);

/*
** srcs/utils/. ---------------------------------------------------------------
*/

/*
**	fd.c
*/

void				set_fd_for_single_cmd(char **cmd_tab, int *fd);
void				restore_std_for_single_cmd(char **cmd_tab, int *fd);
void				set_fd_for_left_pipped_cmd(char **cmd_tab,
					int tube[2], int *fd);
void				set_fd_for_right_pipped_cmd(char **cmd_tab,
					int tube[2], int *fd);
void				restore_std_for_pipped_cmd(int tube[2],
					int *fd, char **args);
void				read_fd(void);
/*
**	args.c
*/

int					nb_args_wo_offset(char **cmd_tab);
void				parse_cmd_tab_left(char **cmd_tab, int i, char **left_args,
					int printnotfound);
char				**format_args(char **cmd_tab, int printnotfound);
void				parse_cmd_tab_right(char **cmd_tab, int j, int i,
					char **right_args);
char				**format_args_after_pipe(char **cmd_tab);

/*
**	signal.c
*/

int					*shell_is_running_cmd(void);
void				put_nl_and_prompt(int signum);
void				listen_sig(void);

/*
**	helpers.c
*/

int					count_arg(char **s);
int					arg_is_in_quotes(char *arg);
int					right_redirected_cmd(char **cmd_tab);
int					left_redirected_cmd(char **cmd_tab);
int					get_fd(char **args);
/*
**	free.c
*/

void				free_cmds(char *line, char **cmds);
void				free_env();
void				free_and_exit(int exit_value, char *msg);

/*
** srcs/parse/. ---------------------------------------------------------------
*/

/*
**	split_cmds_1.c
*/

char				**ft_split_cmds(char *s, char *set);

/*
**	split_cmds_2.c
*/

int					is_in_quotes(char *s, int i);

/*
**	errors.c
*/

int					pattern_isnt_in_quotes(char *line, char *pattern);
int					parse_error(char *line);
int					multilines(char *s);

/*
**	split_cmd_1.c
*/

char				**ft_split_set_quotes_redirects(char *s);
int					ft_new_str_with_quotes(char *s, char *quote,
					char **strs, int *str_i);
int					ft_new_str_redirect(char *s, char *quote,
					char **strs, int *str_i);
int					ft_new_str(char *s, int *i, char **strs, int *str_i);
int					ft_str_pipe(char **strs, int *str_i);

/*
**	split_cmd_2.c
*/

void				ft_inc_to_closing_quote(int *i, char *s);
void				ft_inc_to_end_of_word(int *i, char *s);
int					nb_new_s(char *s);

/*
**	split_cmd_3.c
*/

int					ft_str_with_quotes(char *s, int *i, char **strs,
					int *str_i);
int					ft_str_with_redirect(char *s, int *i, char **strs,
					int *str_i);
int					ft_create_strs(char *s, char **strs, int *str_i);

/*
**	split_cmd_4.c
*/

/*
**	split_cmd_5.c
*/

int					is_separator(char c);
int					is_quote(char c);
int					is_redirect(char c);

#endif
