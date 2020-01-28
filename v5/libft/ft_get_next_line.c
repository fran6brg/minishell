/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:45:15 by fberger           #+#    #+#             */
/*   Updated: 2019/12/02 00:01:21 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			cp_str_until_nl_into_line(char **str, char **line)
{
	int				index;

	index = 0;
	while ((*str)[index] != '\0' && (*str)[index] != '\n')
		index++;
	if (!(*line = ft_substr(*str, 0, index)))
		return (-1);
	if ((*str)[index] == '\0')
	{
		ft_strdel(str);
		return (0);
	}
	else
	{
		*str = ft_strcpy(*str, (*str + index) + 1);
		return (1);
	}
}

int					get_next_line(const int fd, char **line)
{
	int				ret;
	char			buff[BUFFER_SIZE + 1];
	char			*ptr;
	static char		*str[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!str[fd] && !(str[fd] = ft_strnew(0)))
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ptr = str[fd];
		if (!(str[fd] = ft_strjoin(str[fd], buff)))
			return (-1);
		free(ptr);
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (ft_strlen(str[fd]))
		return (cp_str_until_nl_into_line(&str[fd], line));
	else if (ret < 0 || !(*line = ft_strdup(str[fd])))
		return (-1);
	ft_strdel(&str[fd]);
	return (0);
}
