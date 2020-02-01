/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:02:57 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 02:06:56 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_accepted_type(char c)
{
	return (ft_strchr("cspdiouxXf%buUZ", c) ? 1 : 0);
}

static int		is_accepted_flags(char c)
{
	return ((ft_strchr(" .#0+-hlLzj*", c) || ft_isdigit(c)) ? 1 : 0);
}

/*
** calcule la taille dans format et vérifie la validité de l'option
*/

int				compute_flen(const char *format, int i)
{
	int			len;

	len = 1;
	while (is_accepted_flags(format[i + len]))
		len++;
	return (is_accepted_type(format[i + len]) ? len : 0);
}

static void		push_back_new_option(t_options **option, t_options *new)
{
	t_options	*latest;

	if (!option)
		return ;
	if (!(*option))
		*option = new;
	else
	{
		latest = *option;
		while (latest->next)
			latest = latest->next;
		latest->next = new;
	}
}

/*
** extract_options()
** pour chaque option : initie la liste ou push_back le maillon
*/

int				extract_options(const char *format, t_options **options,
				va_list *args)
{
	int			i;
	t_options	*new;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%' && !format[i + 1])
			;
		else if (format[i] == '%')
		{
			if (!(new = (t_options*)ft_memalloc(sizeof(t_options))))
				return (0);
			if (!(init_option(format, new, i, args)))
				return (0);
			push_back_new_option(options, new);
			i += new->flen;
		}
	}
	return (1);
}
