/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:56:52 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 16:19:26 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** free 2D str array
*/

void	ft_free_str_tab(char **strs)
{
	int i;

	i = -1;
	while (strs && strs[++i])
	{
		if (strs[i])
			ft_strdel(&strs[i]);
	}
	if (strs)
	{
		free(strs);
		strs = NULL;
	}
}
