/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:58:14 by fberger           #+#    #+#             */
/*   Updated: 2019/11/16 18:58:36 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unbrlen(uintmax_t value, int base)
{
	int		len;

	len = 1;
	if (base <= 1)
		return (0);
	if (value < 0)
		value = -value;
	while (value >= (uintmax_t)base && len++)
		value /= base;
	return (len);
}
