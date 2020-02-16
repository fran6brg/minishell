/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_tab_ret.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 07:05:34 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 07:06:03 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_str_tab_ret(char **strs, int ret)
{
	ft_free_str_tab(strs);
	return (ret);
}
