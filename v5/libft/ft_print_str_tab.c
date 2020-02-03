/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:28:47 by fberger           #+#    #+#             */
/*   Updated: 2020/02/03 18:40:15 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_tab(char **s, char *indication)
{
	int i;

	i = -1;
	ft_putstr("\n__________________\n");
	if (indication)
		ft_putstr(indication);
	ft_putstr("\n------------------\n");
	while (s[++i])
	{
		ft_putstr("str_tab[");
		ft_putnbr(i);
		ft_putstr("] = -");
		ft_putstr(s[i]);
		ft_putstr("-\n");
	}
	ft_putstr("__________________\n\n");
}
