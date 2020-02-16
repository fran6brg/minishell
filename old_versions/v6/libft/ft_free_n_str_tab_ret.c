/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_n_str_tab_ret.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 07:04:35 by fberger           #+#    #+#             */
/*   Updated: 2020/01/27 07:04:38 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_n_str_tab_ret(char **strs, int str_i, int ret)
{
	ft_free_n_str_tab(strs, str_i);
	return (ret);
}
