/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/01/15 21:55:28 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_$env_var()
**
** observations :
** echo $PATHfoo renvoie juste un retour à ligne
*/

int is_$env_var(t_env *env, char *var)
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
** parse_filename()
*/

int	parse_filename(char **filename, char **cmd_tab, int pos, int i)
{
	if (cmd_tab[pos][i + 1])
		*filename = ft_substr(cmd_tab[pos], i + 1, ft_next_char_pos(cmd_tab[pos] + i + 1, " "));
	else
	{
		if (cmd_tab[pos + 1])
			*filename = ft_strdup(cmd_tab[pos + 1]);
		else // par ex : 'echo abc >'
		{
			ft_printf("zsh: parse error near `\\n'\n");
			return (0);
		}
	}
	return (1);
}

/*
** is_n_option()
*/

int is_n_option(int i, char **cmd_tab)
{
	int	j;
	int	k;

	if (i == 1 && ft_strequ(cmd_tab[i], "-n"))
		return (1);
	else if (i > 1)
	{
		j = 0;
		while (++j <= i)
		{
			if (!ft_str_start_with(cmd_tab[j], "-n"))
				return (0);
			k = 1;
			while (cmd_tab[j][++k])
			{
				if (cmd_tab[j][k] != 'n')
					return (0);
			}
		}
		return (1);
	}
	return (0);
}

/*
** check_if_option_n()
*/

int check_if_option_n(char **cmd_tab)
{
	int i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (is_n_option(i, cmd_tab))
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

	// printf("cmd_tab[pos] = %s\n", cmd_tab[pos]);
	i = 0;
	i = ft_next_char_pos(cmd_tab[pos] + i, ">");
	append = cmd_tab[pos][i + 1] == '>' ? 1 : 0;
	i += append;
	filename = NULL;
	if (!parse_filename(&filename, cmd_tab, pos, i))
		return (ft_strdel(&filename));
	printf("filename = %s\n", filename);
	if ((fd = open(filename, O_CREAT | O_WRONLY | (append ? O_APPEND : O_TRUNC), 0777)) == -1)
		return (ft_strdel(&filename)); // erreur fd
	i = 0;
	while (cmd_tab[++i])
	{
		if (is_n_option(i, cmd_tab) || is_n_option(i - 1, cmd_tab) || ft_strequ(cmd_tab[i], filename)) // continuer si cmd_tab[i] == -n (option) || si l'arg est le filename
			continue ;
		else
			write(fd, " ", 1);
		printf("%s -%.*s- in %s\n", append ? "append" : "overwrite", (int)ft_next_char_pos(cmd_tab[i], ">"), cmd_tab[i], filename);
		write(fd, cmd_tab[i], ft_next_char_pos(cmd_tab[i], ">"));
		if (ft_strchr(cmd_tab[i], '>'))
			i += 1;
	}
	if (!check_if_option_n(cmd_tab))
		write(fd, "\n", 1);
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

	i = 0;
	if (cmd_tab[1] == 0)
		write(1, "\n", 1);
	else
	{
		i = 0;
		while (cmd_tab[++i])
		{
			if (ft_strchr(cmd_tab[i], '>') && !arg_is_in_quotes(cmd_tab[i]))
				return (apply_redirect(cmd_tab, i));
		}
		i = 0;
		while (cmd_tab[++i])
		{
			// printf("cmd_tab[%d] = -%s-\n", i, cmd_tab[i]);
			if (!is_n_option(i, cmd_tab))
			{
				if (is_$env_var(env, cmd_tab[i]))
					;
				else if (arg_is_in_quotes(cmd_tab[i]))
					write(1, cmd_tab[i] + 1, ft_strlen(cmd_tab[i]) - 1);
				else
					write(1, cmd_tab[i], ft_strlen(cmd_tab[i]));
				if (cmd_tab[i + 1])
					write(1, " ", 1);
			}			
		}
		if (!check_if_option_n(cmd_tab))
			write(1, "\n", 1);
	}
}
