/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 21:45:35 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 18:41:02 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*element;
	t_list	*next;

	element = *alst;
	while (element)
	{
		del(element->content, element->content_size);
		next = element->next;
		free(element);
		element = next;
	}
	*alst = NULL;
}
