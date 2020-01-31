/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 04:57:46 by fberger           #+#    #+#             */
/*   Updated: 2020/01/31 08:53:04 by fberger          ###   ########.fr       */
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
** wait_child_process
*/

void	wait_child_process(pid_t child, int tube[2], int right_side)
{
	int	status;
	
	if (DEBUG)
		printf("inside %s parent pid = %d\n", right_side ? "right" : "left", child);
	if (right_side)
	{
		close(tube[WRITE]);
		close(tube[READ]);
	}
	status = 0;
	waitpid(child, &status, 0);
}

/*
** process_left_child
*/

void	process_left_child(char **cmd_tab, int tube[2], char **left_args)
{
	int	fd;
    pid_t	child_left;

    child_left = fork();
	if (child_left == -1) // 1.err
		exit_process(&tube[2], child_left);
	else if (child_left == 0) // 2.fils
    {
		if (DEBUG)
			printf("inside left process pid = %d\n", child_left);
		if ((fd = get_fd(cmd_tab)) != -1 && right_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
		{
			close(tube[READ]);
			dup2(fd, STDOUT_FILENO);
		}
		else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
		{	
			// close(tube[READ]); // ?
			dup2(fd, STDIN_FILENO);
		}
		else
       	{
			close(tube[READ]);
			dup2(tube[WRITE], STDOUT_FILENO);
		}
		if (DEBUG)
			ft_print_str_tab(left_args, "before sending root args"); // pour debug
		root_args(left_args);
		close((fd && fd != -1) ? fd : -1);
		ft_free_str_tab(left_args);
		exit(EXIT_SUCCESS); // apparently useless
    }
	else // 3.parent
		wait_child_process(child_left, tube, 0);

}

/*
** process_right_child
*/

void	process_right_child(char **cmd_tab, int tube[2], char 		**right_args)
{
	int	fd;
    pid_t   child_right;

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
			dup2(tube[READ], STDIN_FILENO); // ok: on lit sur le stdin == le stdout de left child
			dup2(fd, STDOUT_FILENO); // ok: ecrire sur stdout revient desormais a ecrire sur fd
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
			exit(root_args(right_args));
		else /* or recursive call */
			if (!process_pipeline(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, 1))
				return (ft_free_str_tab(right_args));
		close((fd && fd != -1) ? fd : -1);
		ft_free_str_tab(right_args);
    }
	else // 3. parent
	{
		wait_child_process(child_right, tube, 1);
	}
}

int		process_pipeline(char **cmd_tab, int recursive_call)
{
	int    		tube[2];
	char 		**left_args;
	char 		**right_args;
	
	if (DEBUG)
		printf("**********PIPE*********\n");
	if (DEBUG)
		ft_print_str_tab(cmd_tab, "process_pipeline");
	left_args = NULL;
	right_args = NULL;
	if (!(left_args = get_first_args(cmd_tab)) || !(right_args = get_second_args(cmd_tab)))
		return (0);
	if (pipe(tube) == -1)
		return (0);
    process_left_child(cmd_tab, tube, left_args);
	ft_free_str_tab(left_args); /* nb il faut free apres la fin du pid */
    process_right_child(cmd_tab, tube, right_args);
	ft_free_str_tab(right_args);
	if (recursive_call)
		exit(EXIT_SUCCESS); // seulement si recursif
	if (DEBUG)
		printf("**********END PIPE*********\n");
    return (1);
}