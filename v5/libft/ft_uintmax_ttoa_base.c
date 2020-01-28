/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmax_ttoa_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 02:39:32 by fberger           #+#    #+#             */
/*   Updated: 2019/11/19 03:04:55 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_uintmax_ttoa_base(uintmax_t nbr, char *base)
{
	int			size;
	char		*str;
	const int	baselen = ft_strlen(base);

	size = ft_unbrlen(nbr, baselen);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size--] = '\0';
	while (nbr)
	{
		str[size--] = base[nbr % baselen];
		nbr = nbr / baselen;
	}
	if (nbr == 0 && size == 0)
		str[size--] = '0';
	return (str);
}
