/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:49:36 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 02:07:13 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** helper_str_pad()
** calcule le padding à afficher avant et après str
** 1) padding avec c = ' ' par défaut || '0' si option->left_zeros
** 2) la taille du padding = la largeur prévue - la len à afficher
** laquelle est calculée dans ft_printf_string
** 3) affichage du padding
*/

int			helper_str_pad(t_options *option, int len, int after)
{
	char	c;
	int		padding_size;

	c = (option->left_zeros && !option->left_justify) ? '0' : ' ';
	padding_size = option->width - len;
	if (!after && !option->left_justify)
		if (!(add_nchar_ret(option, c, padding_size)))
			return (0);
	if (after && option->left_justify)
		if (!(add_nchar_ret(option, c, padding_size)))
			return (0);
	return (1);
}

/*
** handle_single_percent()
*/

int			handle_single_percent(const char *format, int i)
{
	char	*tmp;
	int		ret;

	ret = 0;
	if (!(tmp = ft_strtrim(format + i, "%")))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ret = ft_strlen(tmp);
	ft_putstr(tmp);
	ft_strdel(&tmp);
	return (ret);
}

/*
** ft_print_modulo()
*/

int			ft_print_modulo(t_options *option, va_list *args)
{
	if (args)
		;
	if (!(helper_str_pad(option, 1, 0))
		|| !(add_nchar_ret(option, '%', 1))
		|| !(helper_str_pad(option, 1, 1)))
		return (0);
	return (1);
}

/*
** ft_print_char()
** if (!c) alors il faut write 0
*/

int			ft_print_char(t_options *option, va_list *args)
{
	char	c;

	if (!(helper_str_pad(option, 1, 0)))
		return (0);
	c = va_arg(*args, int);
	if (!c)
		option->writezero = option->ret++;
	else if (!(add_nchar_ret(option, c, 1)))
		return (0);
	if (!(helper_str_pad(option, 1, 1)))
		return (0);
	return (1);
}

/*
** ft_print_string()
** 1) len (de la str à afficher) = strlen ou precision
** 2) affiche le padding avant (!after)
** 3) add_nstr_ret() = write la string de longueur len
** 4) affiche le padding après (after)
** else if (option->point && !option->precision && option->width)
** 		len = ft_min(option->precision, ft_strlen(tmp));
** le code ci-dessus a pour but de gérer les tests suivants:
** "'{%.*s}", 5, "42" "'{%.*s}", -5, "42" "'%4.s", "42"
*/

int			ft_print_string(t_options *option, va_list *args)
{
	char	*tmp;
	int		len;

	if (!(tmp = ft_strdup(va_arg(*args, char*))))
		if (!(tmp = ft_strndup("(null)", 6)))
			return (0);
	if (option->precision)
		len = ft_min(option->precision, ft_strlen(tmp));
	else if (option->point && !option->precision && option->width)
		len = ft_min(option->precision, ft_strlen(tmp));
	else if (option->precision_zero)
		len = 0;
	else
		len = ft_strlen(tmp);
	if (!(helper_str_pad(option, len, 0))
		|| !(add_nstr_ret(option, tmp, len))
		|| !(helper_str_pad(option, len, 1)))
		return (0);
	ft_strdel(&tmp);
	return (1);
}
