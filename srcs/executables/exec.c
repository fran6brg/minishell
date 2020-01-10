/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:28:51 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 22:33:26 by fberger          ###   ########.fr       */
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
** Ces appels système retournent zéro s'ils réussissent. En cas d'échec, -1
** est renvoyé, et errno contient le code de l'erreur.
** http://manpagesfr.free.fr/man/man2/stat.2.html
*/

/*
** check() itère sur tous les paths de la variable d'environnement $PATH
** en recherchant l'exécutable demandé (cmds[0])
** 1 - On split $PATH via les ':'
** 2 - On assigne à exec le path + "/" + nom de l'executable demandé
** Exemple : path = "/bin" et "pwd" => exec = "/bin" + "/" + "pwd"
** 3 - On test avec la fonction système stat() et access() si l'on peut exécuter
** l'exécutable se trouvant dans le path exec et si oui on retourne le bon path
** 4 - On test si les stats du fichiers sont compatible :
**     via if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
**     qui check si c'est un fichier ordinaire et si on peut l'exécuter

*/

char *check(char **cmds, struct stat *s, char *path, char *exec)
{
  int i;
  char **tab;

  i = -1;
  tab = ft_strsplit(path, ':');
  while (tab[++i])
  {
    exec = ft_strjoin(tab[i], ft_strjoin("/", cmds[0]));
    if (stat(exec, s) == 0 && access(exec, X_OK) == 0)
      if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
        return (exec);
  }
  ft_printf("minishell: command not found : %s\n", cmds[0]);
  return (0);
}

int    exec(char **cmds, char *path)
{
  pid_t pid;
  char *exec;
  struct stat s;

  exec = 0;
  if ((exec = check(cmds, &s, path, exec)) == 0)
    return (-1);
  pid = fork();
  if (pid == 0)
    execv(exec, cmds);
  else if (pid < 0)
  {
    ft_putstr("Fork Failed\n");
    return (-1);
  }
  wait(&pid);
  return (0);
}
