/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:41:30 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:30 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_base(unsigned long long int value, int b, int specifier)
{
	char					c;
	char					a;
	unsigned long long int	nb;
	static int				ret = 0;

	ret -= ret;
	nb = value;
	a = specifier == 'X' ? 'A' : 'a';
	if (b < 2 || b > 16)
		return (0);
	if (nb >= (unsigned long long)b)
		ft_putnbr_base(nb / b, b, specifier);
	c = (nb % b < 10) ? (nb % b) + '0' : (nb % b) + (a - 10);
	ft_putchar(c);
	ret += 1;
	return (ret);
}
