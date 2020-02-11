/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_wo_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 23:28:03 by bihattay          #+#    #+#             */
/*   Updated: 2020/02/11 16:08:07 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_wo_quotes(const char *s)
{
	char	*trim;
	char	*trim_quotes;

	if (!s || !(trim = ft_strtrim(s, " \t")))
		return (NULL);
	if (s[0] == '\'')
	{
		trim_quotes = ft_strtrim(trim, "'");
		ft_strdel(&trim);
		return (trim_quotes);
	}
	else if (s[0] == '"')
	{
		trim_quotes = ft_strtrim(trim, "\"");
		ft_strdel(&trim);
		return (trim_quotes);
	}
	else
		return (trim);
}
