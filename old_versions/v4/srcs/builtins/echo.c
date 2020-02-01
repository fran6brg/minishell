/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 06:28:34 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** store_filename()
*/

int	store_filename(char **filename, char **cmd_tab, int pos)
{
	if (cmd_tab[pos + 1])
	{
		if (!(*filename = ft_strdup(cmd_tab[pos + 1])))
			return (0);
		return (1);
	}
	else // par ex : 'echo abc >'
	{
		ft_printf("zsh: parse error near `\\n'\n");
		return (0);
	}
}

/*
** parse_filename()
*/

int parse_filename(char **cmd_tab, char **filename, int *fd)
{
	int pos;

	pos = 1;
	while (!ft_strchr(">", cmd_tab[pos][0]))
		pos++;
	pos++; // pour decaler apres le >
	*filename = NULL;
	if (!store_filename(filename, cmd_tab, pos))
		return (0);
	printf("filename = -%s-\n", *filename);
	if ((*fd = open(*filename, O_CREAT | O_WRONLY | (cmd_tab[pos][1] == '>' ? O_APPEND : O_TRUNC), 0777)) == -1)
		return (ft_strdel_ret(filename, 0));
	return (1);
}

/*
** apply_redirect_right()
**
** open || create it with rights as 3rd arg (mode)
** int open(const char *pathname, int flags, mode_t mode);
*/

void apply_redirect_right(char **cmd_tab)
{
	int		i;
	char	*filename;
	int		fd;

	if (!parse_filename(cmd_tab, &filename, &fd))
		return ;
	i = 0;
	while (cmd_tab[++i])
	{
		if (is_n_option(i, cmd_tab) || cmd_tab[i][0] == '>' || cmd_tab[i - 1][0] == '>')
			continue ;
		if (i > 1 && !is_n_option(i - 1, cmd_tab))
			write(fd, " ", 1);
		printf("%s -%.*s- in %s\n", "append || overwrite", (int)ft_next_char_pos(cmd_tab[i], ">"), cmd_tab[i], filename);
		if (is_env_var(cmd_tab[i]))
			write(fd, var_value(cmd_tab[i] + 1), ft_strlen(var_value(cmd_tab[i] + 1)));
		else if (arg_is_in_quotes(cmd_tab[i]))
			write(fd, cmd_tab[i] + 1, ft_next_char_pos(cmd_tab[i], ">") - 2);
		else
			write(fd, cmd_tab[i], ft_next_char_pos(cmd_tab[i], ">"));
	}
	write(fd, "\n", no_option_n(cmd_tab));
	ft_strdel(&filename);
	close(fd);
}

/*
** echo écrit chaque message sur la sortie standard, avec un
** espace  entre  chacun  d'eux, et un saut de ligne après le
** dernier.
** option ’-n’ = ne pas effectuer le saut de ligne final.
**
** observations :
** echo -n -n n'affiche rien
*/

void	builtin_echo(char **cmd_tab)
{
	int i;

	i = 0;
	// printf("right_redirected_cmd(cmd_tab) = %d\n", right_redirected_cmd(cmd_tab));
	if (cmd_tab[1] == 0)
		write(1, "\n", 1);
	else if (right_redirected_cmd(cmd_tab))
		apply_redirect_right(cmd_tab);
	// todo :
	// else if (left_redirected_cmd(cmd_tab))
	// 	apply_redirect_left(cmd_tab);
	else
	{
		i = 0;
		while (cmd_tab[++i])
		{
			if (is_n_option(i, cmd_tab))
				continue ;
			else if (is_env_var(cmd_tab[i]))
				ft_printf("%s", var_value(cmd_tab[i] + 1));
			else if (arg_is_in_quotes(cmd_tab[i]))
				write(1, cmd_tab[i] + 1, ft_strlen(cmd_tab[i]) - 2);
			else
				write(1, cmd_tab[i], ft_strlen(cmd_tab[i]));
			write(1, " ", cmd_tab[i + 1] != 0);
		}
		write(1, "\n", no_option_n(cmd_tab));
	}
}
