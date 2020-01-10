/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_letterequci.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:50:15 by fberger           #+#    #+#             */
/*   Updated: 2020/01/10 21:48:56 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** letter equal case insensitive
*/

int		ft_letterequci(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	else if (c1 >= 'a' && c1 <= 'z')
	{
		if (c2 >= 'a' && c2 <= 'z')
			return (c1 == c2);
		else
			return (c1 - 32 == c2);
	}
	else
	{
		if (c2 >= 'A' && c2 <= 'Z')
			return (c1 == c2);
		else
			return (c1 == c2 - 32);
	}
}
