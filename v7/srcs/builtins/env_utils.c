/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:53:31 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 17:44:15 by fberger          ###   ########.fr       */
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

	if (is_env_var(parsed_name))
	{
		if (!(prefix = ft_substr(*arg, 0, ft_next_char_pos(*arg, "\"$")))
		|| !(tmp = ft_strdup(var_value(parsed_name)))
		|| !(suffix = ft_substr(*arg, start + end + 1, ft_strlen(*arg))))
			return ;
		ft_strdel(arg);
		*arg = ft_strjoin_ter(prefix, tmp, suffix);
		ft_strdel(&prefix);
		ft_strdel(&suffix);
		ft_strdel(&tmp);
	}
	else
	{
		ft_strdel(&parsed_name);
		parsed_name = *arg;
		ft_strdel(arg);
		*arg = ft_substr(parsed_name, 0, start - 1);
	}
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
	char	*parsed_name;

	i = 0;
	replace_by_status(cmd_tab, 0);
	while (!ft_strequ(cmd_tab[0], "unset") && cmd_tab[++i])
	{
		if (!ft_strchr(cmd_tab[i], '$') || ft_strstr(cmd_tab[i], "'$")
		|| replace_by_status(cmd_tab, i))
			continue;
		start = ft_next_char_pos(cmd_tab[i], "\"$") + 1;
		start += cmd_tab[i][start + 1] == '$' ? 1 : 0;
		start += cmd_tab[i][start + 1] == '(' ? 1 : 0;
		end = ft_next_char_pos(cmd_tab[i] + start, ")\"");
		parsed_name = ft_substr(cmd_tab[i], start, end);
		concat_and_replace(cmd_tab + i, start, parsed_name, end);
	}
}

/*
** push_back_var()
**
** self-explained
*/

void	push_back_var(char *name, char *value)
{
	t_env	*var;
	t_env	*new;

	if (!name)
		return ;
	var = g_env;
	while (var)
	{
		if (ft_strequ(var->name, name))
		{
			ft_strdel(&var->value);
			var->value = ft_strdup(value);
			return ;
		}
		var = var->next;
	}
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return ;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	var = g_env;
	while (var->next)
		var = var->next;
	var->next = new;
}

/*
** remove_var()
*/

void	remove_var(char *arg)
{
	t_env	*previous;
	t_env	*current;
	t_env	*next;

	current = g_env;
	previous = g_env;
	while (current)
	{
		next = current->next;
		if (ft_strequ(current->name, arg)
		|| (arg[0] == '$' && ft_strequ(current->name, arg + 1)))
		{
			g_env = (current == g_env) ? next : g_env;
			previous->next = next;
			ft_strdel(&current->name);
			ft_strdel(&current->value);
			free(current);
		}
		previous = current;
		current = current->next;
	}
}
