/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 04:29:25 by fberger           #+#    #+#             */
/*   Updated: 2020/02/07 14:57:04 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*g_env;

/*
** var_value()
**
** get value for var name
** ft_strequci ci = case insensitive
*/

char	*var_value(char *name)
{
	char	*trim;
	t_env	*var;

	trim = NULL;
	if (!(trim = ft_strtrim_set(name, "$()\"")))
		return (0);
	var = g_env;
	while (var)
	{
		if (ft_strequ(var->name, trim))
		{
			ft_strdel(&trim);
			return (var->value);
		}
		var = var->next;
	}
	ft_strdel(&trim);
	return (NULL);
}

/*
** builtin_env()
**
** print toutes les var d'env
*/

void	builtin_env(void)
{
	t_env	*var;

	var = g_env;
	while (var)
	{
		if (ft_strlen(var->value) > 0)
		{
			write(1, var->name, ft_strlen(var->name));
			write(1, "=", 1);
			write(1, var->value, ft_strlen(var->value));
			write(1, "\n", 1);
		}
		var = var->next;
	}
	*last_cmd_exit() = EXIT_SUCCESS;
}

/*
** builtin_export()
**
** ajoute une var d'env
** si elle existe déja, la valeur de la variable est modifiée
** autrement, une nouvelle variable est créée
**
** observations :
** setenv n'existe pas sur ZSH
*/

void	builtin_export(char **cmd_tab)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (cmd_tab[++i])
	{
		if (cmd_tab[i][0] == '=')
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
			cmd_tab[i]);
			*last_cmd_exit() = EXIT_FAILURE;
			return ;
		}
		else if (cmd_tab[i][0])
		{
			parse_name_and_value(cmd_tab[i], &name, &value);
			if (name)
				push_back_var(name, value);
		}
	}
	display_declared_vars(i);
	*last_cmd_exit() = EXIT_SUCCESS;
}

/*
** builtin_unsetenv() supprime toutes les var d'env ayant le même nom.
** si aucune variable ne porte ce nom, le programme ne fait rien
*/

void	builtin_unsetenv(char **cmd_tab)
{
	int		i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (ft_strchr(cmd_tab[i], '='))
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n",
			cmd_tab[i]);
			*last_cmd_exit() = EXIT_FAILURE;
		}
		else
		{
			remove_var(cmd_tab[i]);
			*last_cmd_exit() = EXIT_SUCCESS;
		}
	}
}

/*
** builtins_env()
*/

void	builtins_env(char **cmd_tab)
{
	if (ft_strequci(cmd_tab[0], "env"))
		builtin_env();
	else if (ft_strequci(cmd_tab[0], "export"))
		builtin_export(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "unset"))
		builtin_unsetenv(cmd_tab);
}
