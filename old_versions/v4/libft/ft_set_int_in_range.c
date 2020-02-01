/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_int_in_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:30:23 by fberger           #+#    #+#             */
/*   Updated: 2019/12/13 17:30:26 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_set_int_in_range(int min, int nb, int max)
{
	if (nb < min)
		nb = min;
	if (nb > max)
		nb = max;
	return (nb);
}
