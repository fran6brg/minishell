/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 02:59:11 by fberger           #+#    #+#             */
/*   Updated: 2020/01/28 08:23:15 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** t_functions_pointers
** {'D', &ft_print_integer} à inclure
*/

t_functions_pointers	g_option_to_function[NB_ACCEPTED_OPTIONS] =
{
	{'c', &ft_print_char},
	{'s', &ft_print_string},
	{'p', &ft_print_base},
	{'d', &ft_print_integer},
	{'i', &ft_print_integer},
	{'o', &ft_print_base},
	{'u', &ft_print_base},
	{'U', &ft_print_base},
	{'x', &ft_print_base},
	{'X', &ft_print_base},
	{'b', &ft_print_base},
	{'f', &ft_print_floats},
	{'%', &ft_print_modulo}
};

/*
** free_options()
*/

static int		free_options(t_options **options)
{
	t_options	*tmp;
	t_options	*option;

	option = *options;
	while (option)
	{
		ft_strdel(&(option->flags));
		ft_strdel(&(option->output));
		tmp = option;
		option = option->next;
		ft_memdel((void **)&tmp);
	}
	return (1);
}

/*
** get_option_output()
** itération sur la structure ci-dessus pour dispatch vers la fonction
** associée au type
*/

static int		get_option_output(t_options *option, va_list *args)
{
	int			i;

	i = -1;
	while (++i < NB_ACCEPTED_OPTIONS)
		if (g_option_to_function[i].option == option->type)
			return (g_option_to_function[i].f(option, args));
	return (0);
}

/*
** print_format()
** affichage de format avec i (static int) pour retenir la position
** du prochain char à afficher, jusqu'au prochain % ou la fin de len
*/

static int		print_format(t_options *opt, const char *format, const int len)
{
	static int	i = 0;
	int			ret;

	ret = 0;
	if (opt)
	{
		if ((opt->fpos - i) < 0)
			return (ret);
		write(1, (char *)format + i, opt->fpos - i);
		ret = opt->fpos - i;
		i += ret;
		i += opt->flen + 1;
	}
	else
	{
		if (ft_strchr(format + i, '%'))
			return (handle_single_percent(format, i));
		write(1, (char *)format + i, len - i);
		ret = len - i;
		i = 0;
	}
	return (ret);
}

static int		ft_print_option_output(t_options *option)
{
	char		c;

	if (option->writezero >= 0)
	{
		c = 0;
		write(1, option->output, option->writezero);
		write(1, &c, 1);
		write(1, option->output + option->writezero,
			ft_strlen(option->output + option->writezero));
	}
	else
		write(1, option->output, ft_strlen(option->output));
	return (option->ret);
}

/*
** ft_printf()
** extract_options() = lecture du format et parsing des % dans une liste chaînée
** puis itération sur cette liste chaînée :
** 	print_format() = write du format
** 	get_option_output() = rooter vers la fonction de gestion du type
*/

int				ft_printf(const char *format, ...)
{
	va_list		args;
	t_options	*options;
	t_options	*option;
	const int	formatlen = ft_strlen(format);
	int			ret;

	if (!format && (ret = ft_print_string(NULL, NULL)))
		return (ret);
	options = NULL;
	va_start(args, format);
	if (!extract_options(format, &options, &args) && free_options(&options))
		return (-1);
	option = options;
	ret = 0;
	while (option || !free_options(&options))
	{
		ret += print_format(option, format, formatlen);
		if (!(get_option_output(option, &args)) && free_options(&options))
			return (-1);
		ret += ft_print_option_output(option);
		option = option->next;
	}
	ret += print_format(NULL, format, formatlen);
	va_end(args);
	return (ret);
}

/*
** moulitest
** decaler le print_format dans get_option_output
** handle gcc warnings
** fsanitize
** trouver une solution pour le malloc strdup null
** ligne 137/138 c biz
*/
