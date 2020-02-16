/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 04:57:46 by fberger           #+#    #+#             */
/*   Updated: 2020/02/05 13:36:09 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** int pipe(int pipefd[2]);
** Cet appel renvoie 0 s'il réussit, ou -1 s'il échoue,
** auquel cas errno contient le code d'erreur.
** http://manpagesfr.free.fr/man/man2/pipe.2.html
**
** pid_t fork(void);
** En cas de succès, le PID du fils est renvoyé au processus parent, et 0 est
** renvoyé au processus fils. En cas d'échec -1 est renvoyé dans le contexte du
** parent, aucun processus fils n'est créé, et errno contient le code d'erreur.
** http://manpagesfr.free.fr/man/man2/fork.2.html
**
** int dup2(int oldfd, int newfd);
** dup() et dup2() créent une copie du descripteur de fichier oldfd.
** dup() et dup2() renvoient le nouveau descripteur, ou -1 s'ils échouent,
** auquel cas errno contient le code d'erreur.
** http://manpagesfr.free.fr/man/man2/dup.2.html
**
** int execv(const char *path, char *const argv[]);
** argv est un tableau de chaînes d'arguments passées au nouveau programme
** Si l'une des fonctions exec() revient, c'est qu'une erreur
** a eu lieu. La valeur de retour est -1, et errno contient le code d'erreur.
** http://manpagesfr.free.fr/man/man3/exec.3.html
**
** pid_t wait(int *status);
** pid_t waitpid(pid_t pid, int *status, int options);
** http://manpages.ubuntu.com/manpages/xenial/fr/man2/wait.2.html
*/

/*
** run_builtin_or_execv()
**
** return 1 if error
** return 0 if success
*/

int		run_builtin_or_execv(char **cmd_tab)
{
	int ret;

	ret = 0;
	if (cmd_is_builtin(cmd_tab))
	{
		if (!reach_builtin_funct(cmd_tab))
			return (1);
	}
	else
	{
		ret = execv(cmd_tab[0], cmd_tab);
		if (ret == -1)
			return (1);
	}
	return (0);
}

/*
** fork_left_cmd
*/

void	fork_left_cmd(char **cmd_tab, int tube[2], char **left_args)
{
	int		fd;
	pid_t	child_left;
	int		ret;

	fd = 0;
	child_left = fork();
	if (child_left == -1)
		exit_process(&tube[2]);
	else if (child_left == 0)
	{
		set_fd_for_left_pipped_cmd(cmd_tab, tube, &fd);
		ret = run_builtin_or_execv(left_args);
		restore_std_for_pipped_cmd(tube, &fd, left_args);
		exit(ret);
	}
	else
		waitpid_and_free_args(child_left, tube, 0, left_args);
}

/*
** fork_right_cmd
*/

void	fork_right_cmd(char **cmd_tab, int tube[2], char **right_args)
{
	int		fd;
	pid_t	child_right;
	int		ret;

	fd = 0;
	child_right = fork();
	if (child_right == -1)
		exit_process(&tube[2]);
	else if (child_right == 0)
	{
		set_fd_for_right_pipped_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1,
		tube, &fd);
		if (count_pipe(cmd_tab) == 1)
		{
			ret = run_builtin_or_execv(right_args);
			restore_std_for_pipped_cmd(tube, &fd, right_args);
			exit(ret);
		}
		else
			run_pipeline(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, 1);
	}
	else
		waitpid_and_free_args(child_right, tube, 1, right_args);
}

/*
** run_pipeline()
*/

int		run_pipeline(char **cmd_tab, int recursive_call)
{
	int			tube[2];
	char		**left_args;
	char		**right_args;

	left_args = NULL;
	right_args = NULL;
	if (!(left_args = format_args(cmd_tab)))
		return (0);
	if (!(right_args = format_args_after_pipe(cmd_tab)))
		return (0);
	if (pipe(tube) == -1)
		return (0);
	fork_left_cmd(cmd_tab, tube, left_args);
	fork_right_cmd(cmd_tab, tube, right_args);
	if (recursive_call)
		exit(EXIT_SUCCESS);
	return (1);
}
