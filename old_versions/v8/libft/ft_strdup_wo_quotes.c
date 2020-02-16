/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_wo_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 23:28:03 by bihattay          #+#    #+#             */
/*   Updated: 2020/02/11 16:31:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_wo_quotes(const char *s)
{
	char	*trim;
	char	*dup;
	int		inquotes;

	if (!s || !(trim = ft_strtrim(s, " \t")))
		return (NULL);
	inquotes = (trim[0] == '\'' || trim[0] == '"') ? 1 : 0;
	dup = ft_strndup(trim + inquotes, ft_strlen(trim) - (inquotes * 2));
	ft_strdel(&trim);
	return (dup);
}
