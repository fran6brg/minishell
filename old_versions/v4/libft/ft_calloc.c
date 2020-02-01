/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:30:41 by fberger           #+#    #+#             */
/*   Updated: 2019/11/19 19:37:16 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	multp;

	multp = count * size;
	if (multp == 0)
		multp = 1;
	if (!(ptr = malloc(multp)))
		return (NULL);
	ft_bzero(ptr, multp);
	return (ptr);
}
