/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:22 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 20:38:09 by fberger          ###   ########.fr       */
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
	if (chdir(dest) == 0)
		return (1);
	else
	{
		printf("chdir(%s) == %d\n", dest, chdir(dest));
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
** PATH_MAX = Maximum number of bytes in a pathname, including the
** terminating null character.
** http://manpagesfr.free.fr/man/man3/getcwd.3.html
*/

void	go_home(t_env *env, char *home, char **cmd_tab)
{
	char *tmp_path;
  	char buf[PATH_MAX - 1];

	tmp_path = getcwd(buf, PATH_MAX - 1);
	if (!change_dir(cmd_tab, home))
    	return ;
  	builtin_setenv(ft_split(ft_strjoin("cd OLDPWD ", tmp_path), ' '), env);
  	tmp_path = getcwd(buf, PATH_MAX - 1);
  	builtin_setenv(ft_split(ft_strjoin("setenv PWD ", tmp_path), ' '), env);
	ft_strdel(&tmp_path);
}

/*
** int chdir(const char *path);
** renvoie 0 s'il réussi, ou -1 s'il échoue
** http://manpagesfr.free.fr/man/man2/chdir.2.html
*/

void	go_slash(t_env *env, char **cmd_tab)
{
	if (env || cmd_tab)
		;
}

/*
** int chdir(const char *path);
** renvoie 0 s'il réussi, ou -1 s'il échoue
** http://manpagesfr.free.fr/man/man2/chdir.2.html
*/

void	go_path(t_env *env, char **cmd_tab)
{
	int slash;
	char *cwd;
	char buf[PATH_MAX - 1];

	// ?
	if (cmd_tab[1] && cmd_tab[1][0] == '~')
	{
		chdir(var_value(env, "HOME"));
		slash = 2;
	}
	// ?
	else if (cmd_tab[1] && cmd_tab[1][0] == '/' && cmd_tab[1][1])
		slash = 1;
	else
	// ?
		slash = 0;
	cwd = getcwd(buf, PATH_MAX - 1);
	// ?
	if (!change_dir(cmd_tab, cmd_tab[1] + slash))
		return ;
	builtin_setenv(ft_split(ft_strjoin("cd OLDPWD ", cwd), ' '), env);
	cwd = getcwd(buf, PATH_MAX - 1);
	builtin_setenv(ft_split(ft_strjoin("setenv PWD ", cwd), ' '), env);
}

/*
** int chdir(const char *path);
** renvoie 0 s'il réussi, ou -1 s'il échoue
** http://manpagesfr.free.fr/man/man2/chdir.2.html
**
** nb_arg = -1; de sorte qu'on ne compte pas 'cd' qui est la cmd
*/

void	builtin_cd(t_env *env, char **cmd_tab)
{
	int nb_arg;

	print_str_split(cmd_tab);
	nb_arg = -1;
	while (cmd_tab[nb_arg] != 0)
		nb_arg++;
	printf("nb_arg = %d\n", nb_arg);
	// error
	if (nb_arg == 2)
		ft_printf("cd: string not in pwd: %s\n", cmd_tab[1]);
	// error
	else if (nb_arg > 2)
		ft_printf("cd: too many arguments\n");
	// <rien> ou ~
	else if (!cmd_tab[1]
	|| (cmd_tab[1][0] == '~' && cmd_tab[1][1] == '\0'))
		go_home(env, var_value(env, "HOME"), cmd_tab);
	// ~/ ou ~/...
	else if ((cmd_tab[1][0] == '~' && cmd_tab[1][1] == '\0')
	|| (cmd_tab[1][0] == '~' && cmd_tab[1][1] == '/'))
		go_slash(env, cmd_tab);
	// path/... ou /path/...
	else
		go_path(env, cmd_tab);
}
