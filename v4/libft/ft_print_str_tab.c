/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:28:47 by fberger           #+#    #+#             */
/*   Updated: 2020/01/25 21:48:38 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_tab(char **s, char *indication)
{
	int i;

	i = -1;
	ft_putstr("\n__________________\n");
	if (indication)
		ft_printf("%s", indication);
	ft_putstr("\n------------------\n");
	while (s[++i])
		ft_printf("str_tab[%d] = -%s-\n", i, s[i]);
	ft_putstr("__________________\n\n");
}
