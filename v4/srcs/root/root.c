/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 05:42:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/26 04:56:24 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** root towards the right function
**
** nb :
** else if (cmd_tab[0]) sert à protéger la fonction execute 
** contre la commande constituee d'une chaine d'espaces + enter
*/

int	root_builtins(char **cmd_tab)
{
	// ft_print_str_tab(cmd_tab, "inside root_builtins"); // pour debug
	if (is_dollar_env_var(cmd_tab[0]))
		ft_printf("%s\n", var_value(cmd_tab[0] + 1));
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

/*
** root_args
*/

void	root_args(char **cmd_tab)
{
	// ft_print_str_tab(cmd_tab, "inside root args"); // pour debug
	replace_dollar_vars(cmd_tab);
	if (is_builtin(cmd_tab))
	{
		if (!root_builtins(cmd_tab))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (execv(cmd_tab[0], cmd_tab) == -1)
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/*
** process_left_child
*/

// void	process_left_child(char **cmd_tab, int pdes[2])
// {
//     int			status;
// 	char 		**left_args;
//     pid_t   	child_left;

// 	status = 0;
// 	left_args = get_first_args(cmd_tab);
// 	child_left = fork();
// 	if (child_left == -1) // 1.err
// 	{
// 		close(pdes[READ]);
// 		close(pdes[WRITE]);
// 		printf("left son pid = %d | FORK FAIL\n", child_left);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (child_left == 0) // 2.fils
//     {
// 		printf("inside left process pid = %d\n", child_left);
//         close(pdes[READ]);
//         dup2(pdes[WRITE], STDOUT_FILENO);
// 		root_args(left_args);
// 		ft_free_str_tab(left_args);
//     }
// 	else // 3.parent
// 		waitpid(child_left, &status, 0);	
// }

// /*
// ** process_right_child
// */

// int	process_right_child(char **cmd_tab, int pdes[2])
// {
//     int			status;
// 	char 		**right_args;
//     pid_t   	child_right;

// 	status = 0;
// 	right_args = get_second_args(cmd_tab);
// 	child_right = fork();
// 	if (child_right == -1) // 1.err
// 	{
// 		close(pdes[READ]);
// 		close(pdes[WRITE]);
// 		printf("right process pid = %d | FORK FAIL\n", child_right);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (child_right == 0) // 2.fils
//     {
// 		printf("inside right son pid = %d\n", child_right);
//         close(pdes[WRITE]);
//         dup2(pdes[READ], STDIN_FILENO);
//         /* execution of last command */
//         if (count_pipe(cmd_tab) == 1)
// 			root_args(right_args);
// 		/* or recursive call */
// 		else
// 		{
// 			ft_print_str_tab(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, "cmd inside child right > exec");
			// if (!process_pipeline(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, 1))
				// return (0);
// 		}
// 		ft_free_str_tab(right_args);
//     }
// 	close(pdes[WRITE]);
// 	close(pdes[READ]);    
// 	waitpid(child_right, &status, 0);
// 	return (1);
// }

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

// int		process_pipeline(char **cmd_tab, int recursive_call)
// {
// 	int    		pdes[2];

// 	printf("**********PIPE*********\n");
// 	ft_print_str_tab(cmd_tab, "process_pipeline");
// 	if (pipe(pdes) == -1)
// 		return (0);
//     process_left_child(cmd_tab, &pdes[2]);
//     if (!process_right_child(cmd_tab, &pdes[2]))
// 		return (0);
//     if (recursive_call)
// 		exit(EXIT_SUCCESS); // seulement si recursif
// 	printf("**********END PIPE*********\n");
//     return (1);
// }

int		process_pipeline(char **cmd_tab, int recursive_call)
{
	int    		pdes[2];
    int			status = 0;
    pid_t   	child_left;
    pid_t   	child_right;
	char 		**left_args = get_first_args(cmd_tab);
	char 		**right_args = get_second_args(cmd_tab);
	int			fd;

	printf("**********PIPE*********\n");
	ft_print_str_tab(cmd_tab, "process_pipeline");
		
	if (pipe(pdes) == -1)
		return (0);
	
    child_left = fork();
	if (child_left == -1) // 1.err
		exit_process(&pdes[2], child_left);
	else if (child_left == 0) // 2.fils
    {
		printf("inside left process pid = %d\n", child_left);
        close(pdes[READ]);
		if (cmd_is_right_redirected(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1)) // todo : get fd of file to open
		{
			fd = get_fd(cmd_tab);
			dup2(fd, STDOUT_FILENO);
		}
		else if (cmd_is_left_redirected(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1)) // todo : get fd of file to open
		{
			; // fd = get_fd(cmd_tab);
			// dup2(fd, STDOUT_FILENO); // ?
		}
		else
       		dup2(pdes[WRITE], STDOUT_FILENO);
		root_args(left_args);
		ft_free_str_tab(left_args);
    }
	else // 3.parent
		waitpid(child_left, &status, 0);	

	status = 0;
	child_right = fork();
	if (child_right == -1) // 1.err
		exit_process(&pdes[2], child_right);
	else if (child_right == 0) // 2.fils
    {
		printf("inside right son pid = %d\n", child_right);
        close(pdes[WRITE]);
		if (cmd_is_right_redirected(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1)) // todo : get fd of file to open
		{
			fd = get_fd(cmd_tab);
			dup2(fd, STDOUT_FILENO);
		}
		else if (cmd_is_left_redirected(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1)) // todo : get fd of file to open
		{
			; // fd = get_fd(cmd_tab);
			// dup2(fd, STDOUT_FILENO); // ?
		}
		else
	   		dup2(pdes[READ], STDIN_FILENO);
        /* execution of last command */
        if (count_pipe(cmd_tab) == 1)
			root_args(right_args);
		/* or recursive call */
		else
		{
			ft_print_str_tab(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, "cmd inside child right > exec");
			if (!process_pipeline(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1, 1))
				return (0);
		}
		close((cmd_is_right_redirected(cmd_tab) && fd) ? fd : -1);
		ft_free_str_tab(right_args);
    }
	else // 3. parent
	{
		close(pdes[WRITE]);
		close(pdes[READ]);    
		waitpid(child_right, &status, 0);
	}

    if (recursive_call)
		exit(EXIT_SUCCESS); // seulement si recursif
	printf("**********END PIPE*********\n");
    return (1);
}