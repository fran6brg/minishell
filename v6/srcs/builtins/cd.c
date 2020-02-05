/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:22 by fberger           #+#    #+#             */
/*   Updated: 2020/02/05 13:02:56 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** int chdir(const char *path);
** renvoie 0 s'il réussi, ou -1 s'il échoue
** http://manpagesfr.free.fr/man/man2/chdir.2.html
**
** int access(const char *pathname, int mode);
** F_OK : Tests whether the file exists.
** R_OK : Tests whether the file can be accessed for reading.
** W_OK : Tests whether the file can be accessed for writing.
** X_OK : Tests whether the file can be accessed for execution.
** L'appel renvoie 0 s'il réussit (toutes les requêtes sont autorisées),
** ou -1 s'il échoue (au moins une requête du mode est interdite),
** auquel cas errno contient le code d'erreur.
** http://manpagesfr.free.fr/man/man2/access.2.html
*/

int		change_dir(char **cmd_tab, char *dest)
{
	int ret;

	if ((ret = chdir(dest)) == 0)
		return (1);
	else
	{
		ft_printf("cd: ");
		if (access(dest, F_OK) == -1)
			ft_printf("no such file or directory: ");
		else if (access(dest, R_OK) == -1)
			ft_printf("permission denied: ");
		else
			ft_printf("not a directory: ");
		ft_printf("%s\n", cmd_tab[1] ? cmd_tab[1] : dest);
		return (0);
	}
}

/*
** char *getcwd(char *buf, size_t size);
**
** RETURN VALUES :
** En cas de réussite buf est renvoyé.
** NULL en cas d'échec, avec errno contenant le code d'erreur.
** Le contenu de la chaîne pointée par buf est indéfini en cas d'erreur.
**
** NB :
** PATH_MAX = Maximum number of bytes in a pathname, including the
** terminating null character.
** http://manpagesfr.free.fr/man/man3/getcwd.3.html
*/

void	go_path(char **cmd_tab, char *dest)
{
	char	*tmp_path;
	char	buf[PATH_MAX - 1];
	char	*cmd;
	char	**cmd_tab_tmp;

	tmp_path = getcwd(buf, PATH_MAX - 1);
	if (!dest || !change_dir(cmd_tab, dest))
		return ;
	cmd = ft_strjoin("cd OLDPWD ", tmp_path);
	cmd_tab_tmp = ft_split(cmd, ' ');
	builtin_export(cmd_tab_tmp);
	ft_strdel(&cmd);
	ft_free_str_tab(cmd_tab_tmp);
	tmp_path = getcwd(buf, PATH_MAX - 1);
	cmd = ft_strjoin("setenv PWD ", tmp_path);
	cmd_tab_tmp = ft_split(cmd, ' ');
	builtin_export(cmd_tab_tmp);
	ft_strdel(&cmd);
	ft_free_str_tab(cmd_tab_tmp);
}

/*
** print_cd_error()
*/

void	print_cd_error(int nb_arg, char **cmd_tab)
{
	if (nb_arg == 3)
		ft_printf("cd: string not in pwd: %s\n", cmd_tab[1]);
	else if (nb_arg > 3)
		ft_printf("cd: too many arguments\n");
}

/*
** get_destination()
**
**  if => 'cd' sans rien derrière
** eif => 'cd -' sans rien derrière
** eif => 'cd -/[...]' avec un chemin derrière
** eif => 'cd ~/[...]' avec un chemin derrière
** eif => 'cd ~' sans rien derrière
** eif => 'cd $HOME' (nb : 'cd $HOMEtruc' fonctionne aussi)
*/

void	get_destination(char **cmd_tab, char **dest)
{
	if (!cmd_tab[1])
		*dest = var_value("$HOME");
	else if (cmd_tab[1][0] == '-' && !cmd_tab[1][1])
	{
		*dest = var_value("$OLDPWD");
		ft_printf("%s\n", var_value("$OLDPWD"));
	}
	else if (cmd_tab[1][0] == '-' && cmd_tab[1][1] == '/')
	{
		*dest = ft_strjoin(var_value("$OLDPWD"), cmd_tab[1] + 1);
		ft_printf("%s\n", var_value("$OLDPWD"));
	}
	else if (cmd_tab[1][0] == '~' && !cmd_tab[1][1])
		*dest = var_value("$HOME");
	else if (cmd_tab[1][0] == '~' && cmd_tab[1][1] == '/')
		*dest = ft_strjoin(var_value("$HOME"), cmd_tab[1] + 1);
	else if (ft_str_start_with(cmd_tab[1], "$HOME"))
		*dest = var_value("$HOME");
	else
		*dest = cmd_tab[1];
}

/*
** int chdir(const char *path);
** renvoie 0 s'il réussi, ou -1 s'il échoue
** http://manpagesfr.free.fr/man/man2/chdir.2.html
*/

void	builtin_cd(char **cmd_tab)
{
	int		nb_arg;
	char	*dest;

	nb_arg = count_arg(cmd_tab);
	if (nb_arg >= 3)
		return (print_cd_error(nb_arg, cmd_tab));
	get_destination(cmd_tab, &dest);
	go_path(cmd_tab, dest);
}
