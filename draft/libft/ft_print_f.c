/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:03:34 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 02:18:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			helper_f(t_options *option, int len, int after, int neg)
{
	int				i;

	i = -1;
	if ((!after && option->left_justify) || (after && !option->left_justify))
		return (1);
	if (option->left_zeros && !option->left_justify)
		if (option->sign || neg == 1)
			if (!(add_nchar_ret(option, neg == 1 ? '-' : '+', 1)))
				return (0);
	while (++i < option->width - (len + neg))
	{
		if (option->left_zeros && !option->left_justify)
		{
			if (!(add_nchar_ret(option, '0', 1)))
				return (0);
		}
		else if (!(add_nchar_ret(option, ' ', 1)))
			return (0);
	}
	if (!option->left_zeros)
		if (option->sign || neg == 1)
			if (!(add_nchar_ret(option, neg == 1 ? '-' : '+', 1)))
				return (0);
	return (1);
}

static int			helper_precision(t_options *o, long double nbr, int p)
{
	int				i;

	i = -1;
	while (++i < p)
	{
		nbr *= 10;
		if (!((p - i) == 1))
		{
			if (!(add_nchar_ret(o, (int)nbr + '0', 1)))
				return (0);
			nbr -= (int)nbr;
		}
	}
	return (1);
}

int					ft_print_floats(t_options *opt, va_list *args)
{
	long double		nbr;
	int				precision;
	int				nbri;

	precision = (opt->precision ? opt->precision : 6);
	nbr = va_arg(*args, double);
	opt->neg = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	nbri = (int)nbr;
	if (!(helper_f(opt, precision + ft_nbrlen(nbri, 10) + 1, 0, opt->neg)))
		return (0);
	if (!(add_unbr_to_output(opt, nbri, "0123456789")))
		return (0);
	if (!(add_nchar_ret(opt, '.', 1)))
		return (0);
	nbr -= (long double)nbri;
	if (!(helper_precision(opt, nbr, precision)))
		return (0);
	if (!(add_nchar_ret(opt, nbr + 0.5 + '0', 1)))
		return (0);
	if (!(helper_f(opt, precision + ft_nbrlen(nbri, 10) + 1, 1, opt->neg)))
		return (0);
	return (1);
}
