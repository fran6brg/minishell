/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_n_str_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 02:43:24 by fberger           #+#    #+#             */
/*   Updated: 2020/01/19 02:43:44 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_n_str_tab(char **strs, int str_i)
{
	if (strs)
	{
		while (str_i-- > 0)
			ft_strdel(&strs[str_i]);
		free(strs);
	}
}
