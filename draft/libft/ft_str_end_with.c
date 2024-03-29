/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 07:29:32 by fberger           #+#    #+#             */
/*   Updated: 2020/02/04 15:12:40 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_end_with(char *str, char *end)
{
	int	i;
	int	j;

	if (!str || !end)
		return (0);
	i = ft_strlen(str);
	j = ft_strlen(end);
	while (j >= 0 && i >= 0)
	{
		if (str[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
