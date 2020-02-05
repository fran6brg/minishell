/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:57:36 by fberger           #+#    #+#             */
/*   Updated: 2020/01/26 23:39:22 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_is_set(char c, char const *set)
{
	int i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

static int	nb_set_to_rm(char const *s1, char const *set)
{
	int i;
	int rm;

	i = -1;
	rm = 0;
	while (s1[++i])
		rm += char_is_set(s1[i], set);
	return (rm);
}

char		*ft_strtrim_set(char const *s1, char const *set)
{
	int		i;
	int		range;
	char	*new_s;
	int		j;

	if (!s1)
		return (NULL);
	range = ft_strlen(s1) - nb_set_to_rm(s1, set);
	if (!(new_s = malloc(sizeof(char) * (range + 1))))
		return (0);
	j = 0;
	i = 0;
	while (s1[i])
	{
		if (!(char_is_set(s1[i], set)))
			new_s[j++] = s1[i];
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}
