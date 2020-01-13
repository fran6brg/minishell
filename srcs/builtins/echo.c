/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/01/13 15:50:26 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** print_env_var()
**
** observations :
** echo $PATHfoo renvoie juste un retour à ligne
*/

int print_env_var(t_env *env, char *var)
{
	if (var[0] == '$')
	{
		if (is_env_var(env, var + 1))
			ft_printf(var_value(env, var + 1));
		return (1);
	}
	return (0);
}

/*
** apply_redirect()
**
** open || create it with rights as 3rd arg (mode)
** int open(const char *pathname, int flags, mode_t mode);
*/

void apply_redirect(char **cmd_tab, int pos)
{
	int		i;
	char	*filename;
	int		append;
	int		fd;
	int		n_option;

	printf("cmd_tab[pos] = %s\n", cmd_tab[pos]);
	i = 0;
	i = ft_next_char_pos(cmd_tab[pos] + i, ">");
	printf("i = %d\n", i);
	append = cmd_tab[pos][i + 1] == '>' ? 1 : 0;
	i += append;
	if (cmd_tab[pos][i + 1])
		filename = ft_substr(cmd_tab[pos], i + 1, ft_next_char_pos(cmd_tab[pos] + i + 1, " "));
	else
	{
		if (cmd_tab[pos + 1])
			filename = ft_strdup(cmd_tab[pos + 1]);
		else // par ex : 'echo abc >'
		{
			ft_printf("zsh: parse error near `\\n'\n");
			return (ft_strdel(&filename));
		}
	}
	printf("filename = %s\n", filename);
	if ((fd = open(filename, O_CREAT | O_WRONLY | (append ? O_APPEND : O_TRUNC), 0777)) == -1)
		return (ft_strdel(&filename)); // erreur fd
	i = 0;
	n_option = 0;
	while (cmd_tab[++i])
	{
		if (i == 1 && ft_str_start_with(cmd_tab[i], "-n"))
			n_option = 1;
		else if (i > 1 && ft_str_start_with(cmd_tab[i - 1], "-n") && ft_str_start_with(cmd_tab[i], "-n"))
			;
		else
		{
			// ne pas afficher d'espace si cmd_tab[1] == -n || cmd_tab[1] == -n && cmd_tab[2] == -n 
			if (i >= 2 + n_option)
				;
			else if (!ft_strequ(cmd_tab[i + 1], filename))
				;
			else
			{
				printf("%s -%s-   in -%s- before -%s-\n", append ? "append" : "overwrite", " ", filename, cmd_tab[i + 1]);
				write(fd, " ", 1);
			}
			printf("%s -%.*s- in %s\n", append ? "append" : "overwrite", (int)ft_next_char_pos(cmd_tab[i], ">"), cmd_tab[i], filename);
			write(fd, cmd_tab[i], ft_next_char_pos(cmd_tab[i], ">"));
			if (ft_strchr(cmd_tab[i], '>') || ft_strequ(cmd_tab[i], filename))
				i += 1;
		}
	}
	if (!n_option)
	{
		printf("newline\n");
		write(fd, "\n", 1);
	}
	close(fd);
	ft_strdel(&filename);
}

/*
** echo écrit chaque message sur la sortie standard, avec un
** espace  entre  chacun  d'eux, et un saut de ligne après le
** dernier.
** option ’-n’ = ne pas effectuer le saut de ligne final.
**
** premier if gère les cas de double -n cf. observations
** else print var || print arg as usual
**
** observations :
** echo -n -n n'affiche rien
*/

void	builtin_echo(t_env *env, char **cmd_tab)
{
	int i;
	int	n_option;

	i = 0;
	n_option = 0;
	if (cmd_tab[1] == 0)
		write(1, "\n", 1);
	else
	{
		while (cmd_tab[++i])
			if (ft_strstr(cmd_tab[i], ">") || ft_strstr(cmd_tab[i], ">>"))
				return (apply_redirect(cmd_tab, i));
		i = 0;
		while (cmd_tab[++i])
		{
			if ((i == 1 || (i > 1 && ft_strequ(cmd_tab[i - 1], "-n")))
			&& ft_strequ(cmd_tab[i], "-n"))
				n_option = 1;
			else
			{
				if (print_env_var(env, cmd_tab[i]))
					;
				else
					ft_printf("%s", cmd_tab[i]);
				if (cmd_tab[i + 1])
					write(1, " ", 1);
			}
		}
		if (!n_option)
			write(1, "\n", 1);
	}
}
