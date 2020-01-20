/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:28:51 by fberger           #+#    #+#             */
/*   Updated: 2020/01/20 05:45:30 by fberger          ###   ########.fr       */
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
		*exec_path = ft_strjoin(tab[i], ft_strjoin("/", cmd_tab[0]));
		if (check_direct_path_to_exec(*exec_path, &s))
			return (1);			
		ft_strdel(exec_path);
		*exec_path = NULL;
	}
	return (0);
}

/*
** fork_and_exec
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
** int execve(const char *fichier, char *const argv[], char *const envp[]); 
** http://manpagesfr.free.fr/man/man2/execve.2.html
*/

int		handle_pipe(char **cmd_tab, char *exec_path)
{
	int    		pdes[2];
    int			status = 0;
	int	const	READ = 0;
	int	const	WRITE = 1;
    pid_t   	child_right;
    pid_t   	child_left;
	char		*args1[3];
	char		*args2[3];

	if (cmd_tab || exec_path || status)
		;
	printf("**********PIPE*********\n");
	args1[0] = "/bin/ls";
	args1[1] = "-lF";
	args1[2] = 0;
	args2[0] = "/bin/cat";
	args2[1] = "-e";
	args2[2] = 0;
    pipe(pdes);
    if (!(child_left = fork()))
    {
        close(pdes[READ]);
        dup2(pdes[WRITE], STDOUT_FILENO);
        /* Execute command to the left of the pipe */
        execv("/bin/ls", args1);
    }
    if (!(child_right = fork()))
    {
        close(pdes[WRITE]);
        dup2(pdes[READ], STDIN_FILENO);
        /* Recursive call or execution of last command */
        execv("/bin/cat", args2);
		// to do : recursive handle_pipe
    }
    /* Should not forget to close both ends of the pipe */
    close(pdes[WRITE]);
    close(pdes[READ]);
    wait(NULL);
    waitpid(child_right, &status, 0);
    // exit(0);
	printf("**********FINAL*********\n");
    return (1);
}

/*
** int execv(const char *path, char *const argv[]);
** http://manpagesfr.free.fr/man/man3/exec.3.html
**
** pid_t fork(void);
** En cas de succès, le PID du fils est renvoyé au processus parent, et 0 est
** renvoyé au processus fils. En cas d'échec -1 est renvoyé dans le contexte du
** parent, aucun processus fils n'est créé, et errno contient le code d'erreur.  
** http://manpagesfr.free.fr/man/man2/fork.2.html
**
** pid_t waitpid(pid_t pid, int *status, int options);
** http://manpages.ubuntu.com/manpages/xenial/fr/man2/wait.2.html
**
** int kill(pid_t pid, int sig);
** http://manpagesfr.free.fr/man/man2/kill.2.html
*/

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
	if (cmd_contains_pipe(cmd_tab) && !handle_pipe(cmd_tab, exec_path))
		ft_putstr("Fork Failed\n");
	else if (!fork_and_exec(cmd_tab, exec_path))
		ft_putstr("Fork Failed\n");
	wait(NULL);
	return (0);
}
