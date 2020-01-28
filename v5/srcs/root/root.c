/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 05:42:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/28 04:05:03 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** single_builtin()
** root towards the right builtin function
**
** nb :
** else if (cmd_tab[0]) sert à protéger la fonction execute 
** contre la commande constituee d'une chaine d'espaces + enter
*/

int	single_builtin(char **cmd_tab)
{
	if (is_env_var(cmd_tab[0]))
		ft_printf("%s\n", var_value(cmd_tab[0]));
	else if (ft_strequci(cmd_tab[0], "echo"))
		builtin_echo(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "cd"))
		builtin_cd(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "pwd"))
		builtin_pwd();
	else if (ft_strequci(cmd_tab[0], "env")
	|| ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export")
	|| ft_strequci(cmd_tab[0], "unset"))
		builtins_env(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "exit"))
		exit_minishell(cmd_tab);
	return (1);
}

void	single_execv(char **cmd_tab)
{
	char	**formated_args;
	pid_t   child;
	int		status;
	int		fd;

	replace_dollar_vars(cmd_tab);
	status = 0;
	if ((formated_args = get_first_args(cmd_tab)))
	{
		if (DEBUG)
			ft_print_str_tab(formated_args, "one shot execv"); // pour debug
		child = fork();
		if (child == -1) // 1.err
			exit(EXIT_FAILURE);
		else if (child == 0) // 2.fils
		{
			fd = get_fd(cmd_tab);
			if (fd != -1 && right_redirected_cmd(cmd_tab))
				dup2(fd, STDOUT_FILENO);
			else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
				dup2(fd, STDIN_FILENO);
			exit((execv(formated_args[0], formated_args) == -1) ? EXIT_FAILURE : EXIT_SUCCESS);
			close((fd && fd != -1) ? fd : -1);
			ft_free_str_tab(formated_args);
		}
		else // 3. parent
		{
			waitpid(child, &status, 0);
			ft_free_str_tab(formated_args);
		}
	}
}

/*
** is_builtin()
*/

int		is_builtin(char **cmd_tab)
{
	return (/* ft_strequci(cmd_tab[0], "echo")
	|| */ ft_strequci(cmd_tab[0], "cd")
	|| ft_strequci(cmd_tab[0], "pwd")
	|| ft_strequci(cmd_tab[0], "env")
	|| ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "unset")
	|| ft_strequci(cmd_tab[0], "exit")
	|| is_env_var(cmd_tab[0])
	);
}

/*
** root_args
*/

int	root_args(char **cmd_tab)
{
	if (DEBUG)
		ft_print_str_tab(cmd_tab, "inside root args"); // pour debug
	if (is_builtin(cmd_tab))
	{
		if (!single_builtin(cmd_tab))
			return (1);
	}
	else
	{
		if (execv(cmd_tab[0], cmd_tab) == -1)
			return (1);
	}
	return (0);
}

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
** process_left_child
*/

int	process_left_child(char **cmd_tab, int pdes[2], char **left_args, pid_t child_left, int status, int fd)
{
	if (DEBUG)
	{
		printf("pdes[0] = %d\n", pdes[0]);
		printf("pdes[1] = %d\n", pdes[1]);
		printf("pdes[2] = %d\n", pdes[2]);
	}
	fd = -1;
	left_args = NULL;
	if (!(left_args = get_first_args(cmd_tab)))
		return (0);
    child_left = fork();
	if (child_left == -1) // 1.err
		exit_process(&pdes[2], child_left);
	else if (child_left == 0) // 2.fils
    {
		if (DEBUG)
			printf("inside left process pid = %d\n", child_left);
        close(pdes[READ]);
		fd = get_fd(cmd_tab);
		if (fd != -1 && right_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
			dup2(fd, STDOUT_FILENO);
		else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
			dup2(fd, STDIN_FILENO);
		else
       		dup2(pdes[WRITE], STDOUT_FILENO);
		exit(root_args(left_args));
		close((fd && fd != -1) ? fd : -1);
		ft_free_str_tab(left_args);
		exit(EXIT_SUCCESS);
    }
	else // 3.parent
	{
		status = 0;
		waitpid(child_left, &status, 0);
		kill(child_left, SIGTERM);
		ft_free_str_tab(left_args); /* nb il faut free apres la fin du pid */
	}
	return (1);
}

// /*
// ** process_right_child
// */

int	process_right_child(char **cmd_tab, int pdes[2], char **right_args, pid_t child_right, int status, int fd)
{
	if (DEBUG)
	{
		printf("pdes[0] = %d\n", pdes[0]);
		printf("pdes[1] = %d\n", pdes[1]);
		printf("pdes[2] = %d\n", pdes[2]);
	}
	fd = -1;
	right_args = NULL;
	if (!(right_args = get_second_args(cmd_tab)))
		return (0);
	child_right = fork();
	if (child_right == -1) // 1.err
		exit_process(&pdes[2], child_right);
	else if (child_right == 0) // 2.fils
    {
		if (DEBUG)
			printf("inside right son pid = %d\n", child_right);
        close(pdes[WRITE]);
		fd = get_fd(cmd_tab);
		if (fd != -1 && right_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
			dup2(fd, STDOUT_FILENO);
		else if (fd != -1 && left_redirected_cmd(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1))
			dup2(fd, STDIN_FILENO);
		else
	   		dup2(pdes[READ], STDIN_FILENO);
		if (DEBUG)
			printf("count_pipe(cmd_tab) = %d\n", count_pipe(cmd_tab));
        if (count_pipe(cmd_tab) == 1) /* execution of last command */
			exit(root_args(right_args));
		else /* or recursive call */
		{
			if (DEBUG)
				ft_print_str_tab(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, "cmd inside child right > exec");
			if (!process_pipeline(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, 1))
				return (ft_free_str_tab_ret(right_args, 0));
		}
		close((fd && fd != -1) ? fd : -1);
		ft_free_str_tab(right_args);
		if (DEBUG)
			printf("ok CLOSE right\n");
		exit(0);
		if (DEBUG)
			printf("ok EXIT right\n");
    }
	else // 3. parent
	{
		if (DEBUG)
			printf("inside right parent pid = %d\n", child_right);
		close(pdes[WRITE]);
		close(pdes[READ]);
		if (DEBUG)
			printf("inside right parent pid = %d\n", child_right);
		status = 0;
		waitpid(child_right, &status, 0);
		kill(child_right, SIGKILL);
		ft_free_str_tab(right_args); /* nb il faut aussi free apres la fin du pid */
	}
	return (1);
}

int		process_pipeline(char **cmd_tab, int recursive_call)
{
	int    		pdes[2];
    int			status = 0;
	char 		**left_args = NULL;
    pid_t   	child_left = 0;
	char 		**right_args = NULL;
    pid_t   	child_right = 0;
	int			fd = -1;
	
	if (DEBUG)
		printf("**********PIPE*********\n");
	if (DEBUG)
		ft_print_str_tab(cmd_tab, "process_pipeline");
		
	if (pipe(pdes) == -1)
		return (0);

    process_left_child(cmd_tab, pdes, left_args, child_left, status, fd);
    process_right_child(cmd_tab, pdes, right_args, child_right, status, fd);

	if (recursive_call)
		exit(EXIT_SUCCESS); // seulement si recursif
	
	if (DEBUG)
		printf("**********END PIPE*********\n");
    return (1);
}