/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:16:52 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 12:13:53 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** path_to_exec_is_valid()
**
** int stat(const char *path, struct stat *buf);
** retourne une structure stat contenant les champs suivants :
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

int		path_to_exec_is_valid(char *tested_path)
{
	struct stat s;

	if (!stat(tested_path, &s) && !access(tested_path, F_OK | X_OK))
	{
		if ((s.st_mode & S_IFREG) && (s.st_mode & S_IXUSR))
			return (1);
	}
	return (0);
}

int		command_not_found_ret(char **cmd_tab)
{

	ft_printf("minishell: %s: command not found\n", cmd_tab[0]);
	*get_exit_status() = 127;
	return (0);
}

int		find_exec_path(char **cmd_tab, char **exec_path)
{
	int		i;
	char	**tab;

	if ((i = -1) && path_to_exec_is_valid(cmd_tab[0])
	&& (*exec_path = ft_strdup(cmd_tab[0])))
		return (1);
	else if (!var_value("$PATH") || ft_str_start_with(cmd_tab[0], "/bin/"))
	{
		*exec_path = ft_strdup(cmd_tab[0]);
		if (!path_to_exec_is_valid(*exec_path))
			return (command_not_found_ret(cmd_tab));
		return (1);
	}
	tab = ft_split(var_value("$PATH"), ':');
	while (tab[++i])
	{
		if (!(*exec_path = ft_strjoin_ter(tab[i], "/", cmd_tab[0])))
			return (ft_free_str_tab_ret(tab, 0));
		if (path_to_exec_is_valid(*exec_path))
			return (ft_free_str_tab_ret(tab, 1));
		ft_strdel(exec_path);
	}
	ft_free_str_tab(tab);
	return (command_not_found_ret(cmd_tab));
}
