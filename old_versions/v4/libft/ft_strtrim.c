/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:42:26 by fberger           #+#    #+#             */
/*   Updated: 2019/11/19 19:38:47 by fberger          ###   ########.fr       */
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
	int j;
	int rm;

	i = -1;
	rm = 0;
	while (s1[++i] && char_is_set(s1[i], set))
		rm++;
	j = ft_strlen(s1);
	while (s1[--j] && char_is_set(s1[j], set) && j > i)
		rm++;
	return (rm);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		range;
	char	*new_s;

	if (!s1)
		return (NULL);
	i = -1;
	range = ft_strlen(s1) - nb_set_to_rm(s1, set);
	if (!(new_s = malloc(sizeof(char) * (range + 1))))
		return (0);
	while (char_is_set(*s1, set))
		s1++;
	while (++i < range)
		new_s[i] = s1[i];
	new_s[i] = '\0';
	return (new_s);
}
