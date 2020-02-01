/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:32:21 by fberger           #+#    #+#             */
/*   Updated: 2019/11/19 19:38:17 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*current;

	if (!lst)
		return (NULL);
	current = ft_lstnew(f(lst->content));
	begin = current;
	while (lst->next)
	{
		lst = lst->next;
		current->next = ft_lstnew(f(lst->content));
		if (0)
			del(lst->content);
		current = current->next;
	}
	return (begin);
}
