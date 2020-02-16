/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_wo_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 23:28:03 by bihattay          #+#    #+#             */
/*   Updated: 2020/02/05 09:38:07 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_wo_quotes(const char *s)
{
	int		i;
	char	*dup;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (s[0] == '\'' || s[0] == '"')
		len -= 2;
	if (!(dup = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[i] && len--)
	{
		dup[i] = s[i + (s[0] == '\'' || s[0] == '"')];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
