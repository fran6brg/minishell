/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:42:55 by fberger           #+#    #+#             */
/*   Updated: 2019/11/06 15:48:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(long long nb)
{
	unsigned long long int	nbr;
	static int				ret = 0;

	nbr = nb;
	ret -= ret;
	if (nb < 0)
		nbr = -nbr;
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar(nbr % 10 + '0');
	ret += 1;
	return (ret);
}
