/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:41:22 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:22 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(long long value, int base)
{
	int		len;
	int		neg;

	neg = 0;
	len = 1;
	if (value < 0)
	{
		value = -value;
		neg = 1;
	}
	if (base == 0)
		return (0);
	while (value >= (long long)base)
	{
		len++;
		value /= base;
	}
	return (len);
}
