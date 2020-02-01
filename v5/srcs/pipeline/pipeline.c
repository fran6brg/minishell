/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 04:57:46 by fberger           #+#    #+#             */
/*   Updated: 2020/02/01 07:48:30 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** int pipe(int pipefd[2]); 
** Cet appel renvoie 0 s'il réussit, ou -1 s'il échoue, auquel cas errno contient le code d'erreur.  
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
** Si l'une des fonctions exec() revient, c'est qu'une erreur a eu lieu. La valeur de retour est -1, et errno contient le code d'erreur.  
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

int	run_builtin_or_execv(char **cmd_tab)
{
	int ret;

	ret = 0;
	if (DEBUG)
		ft_print_str_tab(cmd_tab, "cmd_tab inside root args"); // pour debug
	if (cmd_is_builtin(cmd_tab))
	{
		if (!reach_builtin_funct(cmd_tab))
			return (1);
	}
	else
	{
		if (DEBUG)
			printf("BEFORE RET EXECV\n"); // pour debug
		ret = execv(cmd_tab[0], cmd_tab);
		if (DEBUG)
			printf("RET EXECV = %d\n", ret); // pour debug
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

    child_left = fork();
	if (child_left == -1) // 1.err
		exit_process(&tube[2], child_left);
	else if (child_left == 0) // 2.fils
    {
		if (DEBUG)
			printf("1. inside left process pid = %d\n", child_left);
		close(tube[READ]);
		if ((fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
		{
			dup2(fd, STDOUT_FILENO);
		}
		else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
		{
			dup2(fd, STDIN_FILENO);
		}
		else
       	{
			dup2(tube[WRITE], STDOUT_FILENO);
		}
		if (DEBUG)
			ft_print_str_tab(left_args, "2. before sending root args"); // pour debug
		ret = run_builtin_or_execv(left_args);
		close((fd && fd != -1) ? fd : -1);
		exit(ret); // apparently useless
    }
	else // 3.parent
		waitpid_and_free_args(child_left, tube, 0, left_args);
}

/*
** fork_right_cmd
*/

void	fork_right_cmd(char **cmd_tab, int tube[2], char 		**right_args)
{
	int		fd;
    pid_t   child_right;
	int 	ret;

	child_right = fork();
	if (child_right == -1) // 1.err
		exit_process(&tube[2], child_right);
	else if (child_right == 0) // 2.fils
    {
		if (DEBUG)
			printf("inside right son pid = %d\n", child_right);
		if ((fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
		{
			if (DEBUG)
				printf("before RIGHT dup2 fd = %d\n", fd);
			close(tube[WRITE]); // ok: on close le write car il sert a rien ici
			dup2(tube[READ], STDIN_FILENO); // ok: avec dup2 le stdin de right est le stdout de left child
			dup2(fd, STDOUT_FILENO); // ici il y a un pb ... ? pourtant ecrire sur stdout revient desormais a ecrire sur fd
			if (DEBUG)
				printf("after RIGHT dup2 fd = %d\n", fd);
		}
		else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
		{
			close(tube[WRITE]); // ok: on close le write car il sert a rien ici
			dup2(fd, STDIN_FILENO); // ok
		}
		else
		{
			close(tube[WRITE]); // ok: on close le write car il sert a rien ici
			dup2(tube[READ], STDIN_FILENO); // ok
		}
        if (count_pipe(cmd_tab) == 1) /* execution of last command */
		{
			ret = run_builtin_or_execv(right_args);
			close((fd && fd != -1) ? fd : -1);
			exit(ret);
		}
		else /* or recursive call */
			pipeline(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, 1);
    }
	else // 3. parent
		waitpid_and_free_args(child_right, tube, 1, right_args);
}

/*
** pipeline()
*/

int		pipeline(char **cmd_tab, int recursive_call)
{
	int    		tube[2];
	char 		**left_args;
	char 		**right_args;
	
	if (DEBUG)
		printf("**********PIPE*********\n");
	if (DEBUG)
		ft_print_str_tab(cmd_tab, "pipeline");
	left_args = NULL;
	right_args = NULL;
	if (!(left_args = format_args(cmd_tab))
	|| !(right_args = format_args_after_pipe(cmd_tab)))
		return (0);
	if (pipe(tube) == -1)
		return (0);
    fork_left_cmd(cmd_tab, tube, left_args);
    fork_right_cmd(cmd_tab, tube, right_args);
	if (recursive_call)
		exit(EXIT_SUCCESS); // seulement si recursif
	if (DEBUG)
		printf("**********END PIPE*********\n");
    return (1);
}