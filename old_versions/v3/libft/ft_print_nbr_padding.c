/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_padding.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:02:43 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 02:07:26 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_sign(t_options *option, long long nb)
{
	if (!option->sign_is_print && (option->type == 'd' || option->type == 'i'))
	{
		if (nb < 0)
		{
			if (!(add_nchar_ret(option, '-', 1)))
				return (0);
			option->sign_is_print = 1;
		}
		if (nb >= 0 && option->sign)
		{
			if (!(add_nchar_ret(option, '+', 1)))
				return (0);
			option->sign_is_print = 1;
		}
	}
	return (1);
}

/*
** nb_has_a_sign return 1 si le nb est < 0 ou s'il doit être signé +
*/

static int	nb_has_a_sign(t_options *option, long long nb)
{
	if ((option->type == 'd' || option->type == 'i')
	&& ((option->neg) || (option->sign && nb >= 0)))
		return (1);
	return (0);
}

static int	nb_have_a_prefix(t_options *opt, long long value, int len)
{
	int		ret;

	ret = 0;
	if (len != -125)
		if (opt->type == 'o' && opt->precision > len)
			return (0);
	if (len != -125 && opt->type == 'o'
			&& opt->hashtag && value == 0 && !opt->width)
		return (0);
	if (opt->hashtag || opt->type == 'p')
	{
		if (value == 0 && opt->type != 'p' && opt->type != 'o')
			return (0);
		if (opt->type == 'o')
			ret += 1;
		else if (opt->type == 'x' || opt->type == 'X' || opt->type == 'p')
			ret += 2;
	}
	return (ret);
}

static int	print_prefix(t_options *option, long long value)
{
	int		prefix_size;

	prefix_size = 0;
	if ((prefix_size = nb_have_a_prefix(option, value, -125)) > 0)
	{
		if (prefix_size == 1)
		{
			if (!(add_nchar_ret(option, '0', 1)))
				return (0);
		}
		else
		{
			if (option->type == 'X')
			{
				if (!(add_nstr_ret(option, "0X", 2)))
					return (0);
			}
			else if (!(add_nstr_ret(option, "0x", 2)))
				return (0);
		}
	}
	return (1);
}

/*
** la fonction helper_nb_pad ...
** padding spaces = pour combler la différence entre width et ce qu'on affiche
** padding zeros : cf note 1 ci-dessous
** ...
** add_nchar_ret
*/

int			helper_nb_pad(t_options *o, int len, int after,
			long long nb)
{
	int		spaces;
	int		zeros;

	spaces = o->width - nb_have_a_prefix(o, nb, len) - nb_has_a_sign(o, nb)
	- ft_max(o->precision, len);
	zeros = ft_max(o->precision - len, 0);
	if (!after)
	{
		if (o->left_zeros && !o->point && !o->left_justify && !o->space)
			ft_swap_int(&zeros, &spaces);
		if (!o->left_justify && !(add_nchar_ret(o, ' ', spaces)))
			return (0);
		if (o->space && !nb_has_a_sign(o, nb)
			&& o->width <= ft_max(o->precision, len))
			if (o->type != 'u' && o->type != 'U' && !(add_nchar_ret(o, ' ', 1)))
				return (0);
		if (!(o->type == 'o' && o->precision > len))
			print_prefix(o, nb);
		print_sign(o, nb);
		if (!(add_nchar_ret(o, '0', zeros)))
			return (0);
	}
	if (after && o->left_justify && !(add_nchar_ret(o, ' ', spaces)))
		return (0);
	return (1);
}

/*
** note 1 : "pour les types d, i, o, u, x, X, la précision indique le nombre
** minimal de chiffres à imprimer.
** Si le nombre de chiffres dans l’argument est inférieur à la precision, la
** valeur de sortie est remplie à gauche de zéros.
** La valeur n’est pas tronquée quand le nombre de chiffres dépasse precision."
*/
