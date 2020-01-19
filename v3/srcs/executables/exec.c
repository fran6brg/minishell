/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:28:51 by fberger           #+#    #+#             */
/*   Updated: 2020/01/19 07:01:23 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** replace_dollar_vars();
*/

void	replace_dollar_vars(char **cmd_tab)
{
	int		i;
	char	*tmp;

    i = 0;
    while (cmd_tab[++i])
	{
		if (is_dollar_env_var(cmd_tab[i]))
		{
			tmp = var_value(cmd_tab[i]);
			ft_strdel(&cmd_tab[i]);
			cmd_tab[i] = tmp;
		}
	}
}

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

int		check_paths(char **cmd_tab, struct stat *s, char *path, char **exec_path)
{
	int 	i;
	char	**tab;

	if (!var_value("PATH") || ft_str_start_with(cmd_tab[0], "/bin/"))
	{
		*exec_path = cmd_tab[0];
		return (check_direct_path_to_exec(*exec_path, s));
	}
	i = -1;
	tab = ft_split(path, ':');
	while (tab[++i])
	{
		*exec_path = ft_strjoin(tab[i], ft_strjoin("/", cmd_tab[0]));
		if (check_direct_path_to_exec(*exec_path, s))
			return (1);			
		ft_strdel(exec_path);
		*exec_path = NULL;
	}
	return (0);
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
	pid_t child;
	char *exec_path;
	struct stat s;
	int	status;

	replace_dollar_vars(cmd_tab);
	if (ft_str_start_with(cmd_tab[0], "./") && !access(cmd_tab[0], X_OK))
		exec_path = cmd_tab[0];
	else if (!check_paths(cmd_tab, &s, var_value("PATH"), &exec_path))
	{
		ft_printf("minishell: command not found : %s\n", cmd_tab[0]);
		return (-1);
	}
	if ((child = fork()) == 0)
		execv(exec_path, cmd_tab);
	else if (child == -1)
	{
		ft_putstr("Fork Failed\n");
		return (-1);
	}
	status = 0;
	waitpid(child, &status, 0);
	kill(child, SIGTERM);
	write(1, "\n", ft_strequci(cmd_tab[0], "cat"));
	return (0);
}
