/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_start_with.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:46:04 by fberger           #+#    #+#             */
/*   Updated: 2020/01/13 15:48:21 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_start_with(char *str, char *start)
{
	size_t i;
	size_t j;

	if (!str || !start)
		return (0);
	i = -1;
	j = -1;
	while (start[++j])
	{
		if (str[++i] != start[j])
			return (0);
	}
	return (1);
}
