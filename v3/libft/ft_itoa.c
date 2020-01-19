/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 23:40:59 by fberger           #+#    #+#             */
/*   Updated: 2019/11/19 19:38:47 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nb_len(long long int n)
{
	long long int	mult;
	int				size;

	mult = 10;
	size = 1;
	while (mult <= n)
	{
		mult *= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	int				size;
	int				neg;
	long long int	nb;
	char			*result;

	nb = n;
	neg = 0;
	if (nb < 0 && (neg = 1))
		nb = -nb;
	size = get_nb_len(nb) + neg;
	if (!(result = malloc(sizeof(char) * (size + 1))))
		return (0);
	result[size] = '\0';
	while (--size >= 0)
	{
		result[size] = (nb % 10) + 48;
		nb /= 10;
	}
	if (neg)
		result[size + 1] = '-';
	return (result);
}
