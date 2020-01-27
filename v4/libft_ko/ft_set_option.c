/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 03:33:22 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 01:23:22 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** set_flags()
** if (new->sign) then new->space = 0;
*/

static void	set_flags(t_options *new)
{
	int		i;

	i = -1;
	new->wildcard = 0;
	while ((new->flags)[++i])
	{
		if ((new->flags)[i] == '-')
			new->left_justify = 1;
		if ((new->flags)[i] == '+')
			new->sign = 1;
		if ((new->flags)[i] == ' ')
			new->space = 1;
		if (new->sign)
			new->space = 0;
		if ((new->flags)[i] == '.')
			new->point = 1;
		if ((new->flags)[i] == '#')
			new->hashtag = 1;
		if ((new->flags)[i] == '0'
		&& (i == 0 || !ft_isdigit((new->flags)[i - 1])))
			new->left_zeros = 1;
		if ((new->flags)[i] == '*')
			new->wildcard = 1;
	}
}

/*
** set_width()
** printf("{%*3d}", 5, 0) le 3 l'emporte sur le *
** observation : si * < 0 alors *= -1 + left_justify
*/

static void	set_width(char *flags, t_options *new, va_list *args)
{
	int		i;

	i = -1;
	while (flags[++i] && flags[i] != '.')
	{
		if (flags[i] == '*')
		{
			new->width = va_arg(*args, int);
			if (new->width < 0 && (new->width *= -1))
				new->left_justify = 1;
		}
		if (ft_isdigit(flags[i]) && flags[i] != '0')
		{
			new->width = ft_atoi(flags + i);
			return ;
		}
	}
}

/*
** set_precision()
** observation :
** 1) if (va_arg_ret < 0 || new->type == 'c' || 's' || '%')
** 		alors new->precision doit être <= new->width
** 2) si * == 0 alors p = 0 est appliquée avec option->precision_zero
*/

static void	set_precision(char *flags, t_options *new, va_list *args)
{
	int		i;
	int		va_arg_ret;

	i = -1;
	while (flags[++i] && flags[i] != '.')
		;
	if (flags[i] && flags[i + 1] == '*')
	{
		if ((va_arg_ret = va_arg(*args, int)) < 0)
			new->precision = ft_min(new->width, (va_arg_ret * -1));
		else if (va_arg_ret == 0)
			new->precision_zero = 1;
		else
			new->precision = ft_max(va_arg_ret, 0);
		if (new->type == 'c' || new->type == 's' || new->type == '%')
			if (new->width)
				new->precision = ft_min(new->width, new->precision);
		return ;
	}
	while (flags[i] && flags[++i] && !(new->precision))
	{
		if (ft_isdigit(flags[i]) && flags[i] != '0')
			new->precision = ft_atoi(flags + i);
	}
}

static void	set_size(char *flags, t_options *new)
{
	int		i;

	i = -1;
	while ((new->flags)[++i])
	{
		if (flags[i] == 'h' && flags[i + 1] == 'h' && flags[i - 1] != 'h')
			new->hh = 1;
		else if (flags[i] == 'h' && flags[i + 1] != 'h' && flags[i - 1] != 'h')
			new->h = 1;
		if (flags[i] == 'l' && flags[i + 1] == 'l' && flags[i - 1] != 'l')
			new->ll = 1;
		else if (flags[i] == 'l' && flags[i + 1] != 'l' && flags[i - 1] != 'l')
			new->l = 1;
		if (flags[i] == 'L')
			new->l = 1;
		if (flags[i] == 'j')
			new->j = 1;
		if (flags[i] == 'z')
			new->z = 1;
	}
}

int			init_option(const char *f, t_options *new, int i, va_list *args)
{
	if (!(new->flen = compute_flen(f, i)))
	{
		ft_memdel((void **)&new);
		return (0);
	}
	new->fpos = i;
	new->flags = ft_substr(f, new->fpos + 1, (size_t)(new->flen - 1));
	if (!(new->flags))
		return (0);
	new->type = f[new->fpos + new->flen];
	if (!(new->output = ft_strnew(0)))
		return (0);
	new->ret = 0;
	new->writezero = -1;
	new->sign_is_print = 0;
	set_flags(new);
	new->width = 0;
	new->width_zero = 0;
	set_width(new->flags, new, args);
	new->precision = 0;
	new->precision_zero = 0;
	set_precision(new->flags, new, args);
	set_size(new->flags, new);
	return (1);
}
