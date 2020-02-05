/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:28:26 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 02:07:04 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** add_nchar_ret()
*/

int				add_nchar_ret(t_options *option, char c, int n)
{
	char		*str;
	static char	str2[2] = "\0";

	if (n == 1)
	{
		str2[0] = c;
		if (!(add_str_ret(option, (char *)str2)))
			return (0);
	}
	else if (n > 0)
	{
		if (!(str = (char *)ft_memset((void *)ft_strnew(n), c, n)))
			return (0);
		if (!(add_str_ret(option, str)))
		{
			ft_strdel(&str);
			return (0);
		}
		ft_strdel(&str);
	}
	return (1);
}

/*
** add_str_ret()
*/

int				add_str_ret(t_options *option, char *str)
{
	char		*tmp;

	if (str)
	{
		tmp = option->output;
		if (!(option->output = ft_strjoin(tmp, str)))
		{
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
	}
	option->ret += ft_strlen(str);
	return (1);
}

/*
** add_nstr_ret()
*/

int				add_nstr_ret(t_options *option, char *str, int n)
{
	char		*tmp;
	char		*tmp2;

	if (str && option)
	{
		tmp = option->output;
		if (!(tmp2 = ft_strndup(str, (size_t)n)))
			return (0);
		if (!(option->output = ft_strjoin(tmp, tmp2)))
		{
			ft_strdel(&tmp2);
			return (0);
		}
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	else if (str && !option)
		write(1, str, n);
	option->ret += ft_min(ft_strlen(str), n);
	return (1);
}

/*
** add_nbr_to_output()
*/

int				add_nbr_to_output(t_options *option, intmax_t nbr,
				char *base)
{
	char		*tmp;

	if (!(tmp = ft_intmax_ttoa_base_ws(nbr, base)))
		return (0);
	if (!(add_str_ret(option, tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

/*
** add_unbr_to_output()
*/

int				add_unbr_to_output(t_options *option, uintmax_t nbr,
				char *base)
{
	char		*tmp;

	if (!(tmp = ft_uintmax_ttoa_base(nbr, base)))
		return (1);
	if (!(add_str_ret(option, tmp)))
	{
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (1);
}
