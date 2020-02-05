/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:53:31 by fberger           #+#    #+#             */
/*   Updated: 2020/02/05 10:03:44 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is_env_var()
**
** observations :
** echo $PATHfoo renvoie juste un retour à ligne
*/

int		is_env_var(char *var)
{
	if (var_value(var))
		return (1);
	return (0);
}

/*
** concat_and_replace()
**
** self-explained
*/

void	concat_and_replace(char **arg, int start, char *parsed_name, int end)
{
	char	*prefix;
	char	*tmp;
	char	*suffix;

	if (!(prefix = ft_substr(*arg, 0, ft_next_char_pos(*arg, "$")))
	|| !(tmp = ft_strdup(var_value(parsed_name)))
	|| !(suffix = ft_substr(*arg, start + end + 1, ft_strlen(*arg))))
		return ;
	ft_strdel(arg);
	*arg = ft_strjoin_ter(prefix, tmp, suffix);
	ft_strdel(&prefix);
	ft_strdel(&tmp);
	ft_strdel(&suffix);
}

/*
** replace_dollar_vars()
**
** self-explained
*/

void	replace_dollar_vars(char **cmd_tab)
{
	int		i;
	int		start;
	int		end;
	char	*tmp;

	i = 0;
	while (cmd_tab[++i])
	{
		start = ft_next_char_pos(cmd_tab[i], "$");
		start += cmd_tab[i][start + 1] == '(' ? 2 : 1;
		end = ft_next_char_pos(cmd_tab[i] + start, ")");
		tmp = ft_substr(cmd_tab[i], start, end);
		if (is_env_var(tmp))
			concat_and_replace(cmd_tab + i, start, tmp, end);
		else
		{
			ft_strdel(&tmp);
			tmp = cmd_tab[i];
			ft_strdel(&cmd_tab[i]);
			cmd_tab[i] = ft_substr(tmp, 0, start - 1);
		}
	}
}

/*
** push_back_var()
**
** self-explained
*/

int		push_back_var(char **cmd_tab)
{
	t_env	*var;
	t_env	*new;

	var = g_env;
	while (var)
	{
		if (ft_strequ(var->name, cmd_tab[1]))
		{
			if (!(var->value = ft_strdup(cmd_tab[2])))
				return (0);
			return (1);
		}
		var = var->next;
	}
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->name = ft_strdup(cmd_tab[1]);
	new->value = ft_strdup(cmd_tab[2]);
	new->next = NULL;
	var = g_env;
	while (var->next)
		var = var->next;
	var->next = new;
	return (1);
}
