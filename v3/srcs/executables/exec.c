/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:28:51 by fberger           #+#    #+#             */
/*   Updated: 2020/01/21 06:58:45 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** int stat(const char *path, struct stat *buf);
** retourne une structure stat contenant les champs suivants :
**
** struct stat {
**    dev_t     st_dev;      ID du périphérique contenant le fichier 
**    ino_t     st_ino;      Numéro inœud 
**    mode_t    st_mode;     Protection 
**    nlink_t   st_nlink;    Nb liens matériels 
**    uid_t     st_uid;      UID propriétaire 
**    gid_t     st_gid;      GID propriétaire 
**    dev_t     st_rdev;     ID périphérique (si fichier spécial) 
**    off_t     st_size;     Taille totale en octets 
**    blksize_t st_blksize;  Taille de bloc pour E/S 
**    blkcnt_t  st_blocks;   Nombre de blocs alloués 
**    time_t    st_atime;    Heure dernier accès 
**    time_t    st_mtime;    Heure dernière modification 
**    time_t    st_ctime;    Heure dernier changement état 
** };
** Les attributs suivants correspondent au champ st_mode :
** S_IFREG	0100000	fichier ordinaire
** S_IRWXU	00700	lecture/écriture/exécution du propriétaire
** S_IRUSR	00400	le propriétaire a le droit de lecture
** S_IWUSR	00200	le propriétaire a le droit d'écriture
** S_IXUSR	00100	le propriétaire a le droit d'exécution
** ...
** Ces appels système retournent 0 s'ils réussissent. En cas d'échec, -1
** est renvoyé, et errno contient le code de l'erreur.
** http://manpagesfr.free.fr/man/man2/stat.2.html
**
** access : cf. cd.c
*/

int		check_direct_path_to_exec(char *tested_path, struct stat *s)
{
	if (!stat(tested_path, s) && !access(tested_path, X_OK))
	{
		if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
			return (1);
	}
	return (0);
}

/*
** first check if path || direct path to command instead of exec name
** if not then operate normal case
*/

int		check_paths(char **cmd_tab, char **exec_path)
{
	int 	i;
	char	**tab;
	struct	stat s;

	if (!var_value("PATH") || ft_str_start_with(cmd_tab[0], "/bin/"))
	{
		*exec_path = cmd_tab[0];
		return (check_direct_path_to_exec(*exec_path, &s));
	}
	i = -1;
	tab = ft_split(var_value("PATH"), ':');
	while (tab[++i])
	{
		if (!(*exec_path = ft_strjoin(tab[i], ft_strjoin("/", cmd_tab[0]))))
			return (0);
		// printf("exec_path =%s\n", *exec_path);
		if (check_direct_path_to_exec(*exec_path, &s))
			return (1);			
		ft_strdel(exec_path);
		*exec_path = NULL;
	}
	return (0);
}

/*
** fork_and_exec
**
** int kill(pid_t pid, int sig);
** http://manpagesfr.free.fr/man/man2/kill.2.html
*/

int		fork_and_exec(char **cmd_tab, char *exec_path)
{
	pid_t	child;
	int		status;

	if ((child = fork()) == 0)
		execv(exec_path, cmd_tab);
	else if (child == -1)
		return (0);
	status = 0;
	waitpid(child, &status, 0);
	kill(child, SIGTERM);
	return (1);
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

int		handle_pipe(char **cmd_tab, int recursive_call)
{
	int    		pdes[2];
    int			status = 0;
	int	const	READ = 0;
	int	const	WRITE = 1;
    pid_t   	child_left;
    pid_t   	child_right;
	char 		**left_args = get_left_exec_args(cmd_tab);
	char 		**right_args = get_right_exec_args(cmd_tab);
	int			j;
	int 		nb_pipe = 0;

	j = 0;
	while (cmd_tab[j])
	{
		if (cmd_tab[j][0] == '|')
			nb_pipe++;
		j++;
	}
	printf("nb_pipe = %d\n", nb_pipe);
	
	if (!left_args || !right_args)
	{
		printf("cmd error\n");
		return (0);
	}
	ft_print_str_tab(left_args); // pour debug
	ft_print_str_tab(right_args); // pour debug
    
	if (pipe(pdes) == -1)
	{
		printf("pipe error\n");
		return (0);
	}
	printf("**********PIPE*********\n");

    child_left = fork();
	printf("left = %d\n", child_left);
	if (child_left == -1)
	{
		// close(pdes[READ]);
		// close(pdes[WRITE]);
		printf("Failed | left = %d\n", child_left);
		return (0);
	}
	else if (child_left == 0)
    {
		printf("Sucess | left = %d\n", child_left);
        close(pdes[READ]);
        dup2(pdes[WRITE], STDOUT_FILENO);
        /* Execute command to the left of the pipe */
        if (execv(left_args[0], left_args) == -1)
			printf("ERROR EXECV\n");
		// exit(0); // pq ca ne change rien ?
    }
	child_right = fork();
    printf("right = %d\n", child_left);
	if (child_right == -1)
	{
		// close(pdes[READ]);
		// close(pdes[WRITE]);
		printf("Failed | right = %d\n", child_left);
		return (0);
	}
	else if (child_right == 0)
    {
		printf("Sucess | right = %d\n", child_right);
        close(pdes[WRITE]);
        dup2(pdes[READ], STDIN_FILENO);
        /* Recursive call or execution of last command */
		printf("nb_pipe = %d\n", nb_pipe);
        if (nb_pipe <= 1)
		{
			if (execv(right_args[0], right_args) == -1)
				printf("ERROR EXECV\n");
		}
		else // to do : recursive handle_pipe
		{
			j = 0;
			while (cmd_tab[j] && cmd_tab[j][0] != '|')
				j++;
			j++;
			ft_print_str_tab(cmd_tab + j);
			if (!handle_pipe(cmd_tab + j, 1))
				return (0);
		}
		// exit(0);
    }
    /* Should not forget to close both ends of the pipe */
    close(pdes[WRITE]);
    close(pdes[READ]);
    wait(NULL); // ?
    waitpid(child_right, &status, 0);
    if (recursive_call)
		exit(0); // seulement si recursif ?
	ft_free_str_tab(left_args);
	ft_free_str_tab(right_args);
	printf("**********FINAL*********\n");
    return (1);
}

int		execute(char **cmd_tab)
{
	char *exec_path;

	replace_dollar_vars(cmd_tab);
	if (ft_str_start_with(cmd_tab[0], "./") && !access(cmd_tab[0], X_OK))
		exec_path = cmd_tab[0];
	else if (!check_paths(cmd_tab, &exec_path))
	{
		ft_printf("minishell: command not found : %s\n", cmd_tab[0]);
		return (0);
	}
	if (cmd_contains_pipe(cmd_tab))
	{
		handle_pipe(cmd_tab, 0);
	}
	else if (!fork_and_exec(cmd_tab, exec_path))
		ft_putstr("Fork Failed\n");
	return (0);
}
