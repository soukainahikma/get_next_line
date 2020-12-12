/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:41:05 by shikma            #+#    #+#             */
/*   Updated: 2020/01/01 14:51:52 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	size_of_line(char *buff)
{
	size_t i;

	i = 0;
	while (buff[i] != '\n')
		i++;
	return (i);
}

int		end_of_line(char **line, char **tmp, char **buff)
{
	*line = *tmp;
	free(*buff);
	return (0);
}

int		ft_reste(char **line, char **tmp, char **buff)
{
	size_t i;

	i = size_of_line(*tmp);
	*line = ft_substr(ft_strdup(*tmp), 0, i);
	*tmp = ft_substr(*tmp, i + 1, ft_strlen(*tmp));
	free(*buff);
	return (1);
}

int		ft_error(int fd, char **line, char **buff)
{
	if (line == NULL)
		return (-1);
	if ((!(*buff = (char *)malloc(BUFFER_SIZE + 1))))
		return (-1);
	if (fd < 0 || read(fd, *buff, 0) < 0 || BUFFER_SIZE < 0)
	{
		free(*buff);
		return (-1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*tmp;
	long long	l;

	if (!tmp)
		tmp = ft_strdup("");
	if (ft_error(fd, line, &buff) == -1)
		return (-1);
	while ((!(ft_strchr(tmp, '\n'))) &&
			(l = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[l] = '\0';
		tmp = ft_strjoin(tmp, buff);
		if ((ft_strchr(tmp, '\n')))
			return (ft_reste(line, &tmp, &buff));
	}
	if (l == 0 && (!(ft_strchr(tmp, '\n'))))
		return (end_of_line(line, &tmp, &buff));
	free(buff);
	buff = NULL;
	if ((ft_strchr(tmp, '\n')))
		return (ft_reste(line, &tmp, &buff));
	free(tmp);
	return (0);
}
