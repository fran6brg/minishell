/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:27:02 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 02:07:09 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** get_str_base()
*/

static char			*get_str_base(t_options *option)
{
	if (option->type == 'b')
		return ("01");
	else if (option->type == 'o' || option->type == 'O')
		return ("01234567");
	else if (option->type == 'u' || option->type == 'U')
		return ("0123456789");
	else if (option->type == 'x' || option->type == 'p')
		return ("0123456789abcdef");
	else if (option->type == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

/*
** get_unsigned_type()
*/

static uintmax_t	get_unsigned_type(t_options *option, va_list *args)
{
	uintmax_t		n;

	n = 0;
	if (option->l)
		n = va_arg(*args, unsigned long);
	else if (option->ll)
		n = va_arg(*args, unsigned long long);
	else if (option->h)
		n = (unsigned short)va_arg(*args, int);
	else if (option->hh)
		n = (unsigned char)va_arg(*args, int);
	else if (option->j)
		n = va_arg(*args, uintmax_t);
	else if (option->type == 'p')
		n = va_arg(*args, unsigned long long);
	else if (option->z)
		n = va_arg(*args, size_t);
	else
		n = va_arg(*args, unsigned int);
	return (n);
}

/*
** la fonction ft_printf_base ... à cleaner
** 1) obtention de la base
** 2) get_unsigned_type() car p / o / u / U / x / X
** 3) affichage de l'espace si le flag est présent
** 4) ...
*/

int					ft_print_base(t_options *o, va_list *args)
{
	char			*base;
	uintmax_t		nbr;
	int				len;

	base = get_str_base(o);
	nbr = get_unsigned_type(o, args);
	len = ft_unbrlen(nbr, ft_strlen(base));
	if (o->space && !o->sign && o->type != 'u' && o->type != 'U')
		if (!(add_nchar_ret(o, ' ', 1)))
			return (0);
	if ((nbr == 0 && o->point && !o->precision && o->type != 'p')
		|| (nbr == 0 && o->type == 'o' && o->hashtag))
		len = 0;
	if (!(helper_nb_pad(o, len, 0, nbr)))
		return (0);
	if (!(nbr == 0 && o->point && !o->precision && o->type != 'p'))
		if (!(nbr == 0 && o->type == 'o' && o->hashtag)
			&& !(nbr == 0 && o->type == 'p' && o->point && !o->precision))
			if (!(add_unbr_to_output(o, nbr, base)))
				return (0);
	if (!(helper_nb_pad(o, len, 1, nbr)))
		return (0);
	return (1);
}
