/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:39:00 by fberger           #+#    #+#             */
/*   Updated: 2019/11/05 19:00:32 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*sptr;
	int		i;

	sptr = (char *)s;
	i = -1;
	while (sptr[++i])
	{
		if (sptr[i] == (char)c)
			return (sptr + i);
	}
	if ((char)c == '\0')
		return (sptr + i);
	return ((char *)0);
}
