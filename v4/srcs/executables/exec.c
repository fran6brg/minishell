/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:28:51 by fberger           #+#    #+#             */
/*   Updated: 2020/01/26 05:20:03 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
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

int		path_to_exec_is_valid(char *tested_path, struct stat *s)
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

	// ft_print_str_tab(cmd_tab, "INSIDE CHECK PATH\n");
	if (!var_value("PATH") || ft_str_start_with(cmd_tab[0], "/bin/"))
	{
		*exec_path = cmd_tab[0];
		return (path_to_exec_is_valid(*exec_path, &s));
	}
	i = -1;
	tab = ft_split(var_value("PATH"), ':');
	while (tab[++i])
	{
		if (!(*exec_path = ft_strjoin(tab[i], ft_strjoin("/", cmd_tab[0]))))
			return (0);
		// printf("exec_path =%s\n", *exec_path);
		if (path_to_exec_is_valid(*exec_path, &s))
			return (1);			
		ft_strdel(exec_path);
		*exec_path = NULL;
	}
	ft_printf("minishell: command not found : %s\n", cmd_tab[0]);
	return (0);
}

/*
** get_first_args();
** meaning before pipe if pipe
** here j is used to skip '>' || '>>' || <filename> args
*/

char **get_first_args(char **cmd_tab)
{
    int     i;
    char    **left_args;
	int		offset;

	i = next_pipe_pos_or_len(cmd_tab);
    if (!(left_args = malloc(sizeof(char *) * (i + 1))))
        return (NULL);
    left_args[i] = NULL;
    i = 0;
	offset = 0;
    while (cmd_tab[i] && cmd_tab[i][0] != '|')
    {
        if (i == 0)
        {
            left_args[0] = NULL;
            if (is_builtin(cmd_tab))
                left_args[i] = ft_strdup(cmd_tab[i]);
            else
                check_paths(cmd_tab, left_args);
        }
		else if (ft_strchr("<>", cmd_tab[i][0]) || ft_strchr(">", cmd_tab[i - 1][0]))
			offset++;
        else
            left_args[i - offset] = ft_strdup(cmd_tab[i]);
        i++;
    }
	while (offset)
		left_args[i - offset--] = NULL;
	ft_print_str_tab(left_args, "inside first_args");
    return (left_args);
}

/*
** get_second_args();
** meaning after pipe
** here k is used to skip '>' || '>>' || <filename> args
*/

char **get_second_args(char **cmd_tab)
{
    int 	i;
    int 	j;
    char    **right_args;
	int		offset;

    i = next_pipe_pos_or_len(cmd_tab) + 1;
    j = i + next_pipe_pos_or_len(cmd_tab + i);
    if (!(right_args = malloc(sizeof(char *) * (j - i + 1))))
        return (NULL);
    right_args[j - i] = NULL;
    j = i;
	offset = 0;
    while (cmd_tab[j] && cmd_tab[j][0] != '|')
    {
        if (j == i)
        {
            right_args[0] = NULL;
            if (is_builtin(cmd_tab + j))
                right_args[j - i] = ft_strdup(cmd_tab[j]);
            else
                check_paths(cmd_tab + j, right_args);
        }
		else if (ft_strchr("<>", cmd_tab[j][0]) || ft_strchr(">", cmd_tab[j - 1][0]))
			offset++;
        else
            right_args[j - i - offset] = ft_strdup(cmd_tab[j]);
        j++;
    }
	while (offset)
		right_args[j - i - offset--] = NULL;
	ft_print_str_tab(right_args, "inside second_args");
    return (right_args);
}

/*
** single_execv()
*/

void	single_execv(char **cmd_tab)
{
	char	**formated_args;
	pid_t   child;
	int		status;
	int		fd;

	status = 0;
	if ((formated_args = get_first_args(cmd_tab)))
	{
		ft_print_str_tab(formated_args, "one shot execv"); // pour debug
		child = fork();
		if (child == -1) // 1.err
			exit(EXIT_FAILURE);
		else if (child == 0) // 2.fils
		{
			if (cmd_is_right_redirected(cmd_tab))
			{
				fd = get_fd(cmd_tab);
				dup2(fd, STDOUT_FILENO);
				// dup2(fd, STDERR_FILENO); // to debug
			}
			else if (cmd_is_left_redirected(cmd_tab + next_pipe_pos_or_len(cmd_tab) + 1)) // todo : get fd of file to open
			{
				fd = get_fd(cmd_tab);
				dup2(fd, STDIN_FILENO);
			}
			exit((execv(formated_args[0], formated_args) == -1) ? EXIT_FAILURE : EXIT_SUCCESS);
			close((cmd_is_right_redirected(cmd_tab) && fd) ? fd : -1);
		}
		else // 3. parent
			waitpid(child, &status, 0);
		ft_free_str_tab(formated_args);
	}
}