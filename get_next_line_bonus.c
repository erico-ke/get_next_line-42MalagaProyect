/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:13:36 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/12 18:19:01 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_newline(int fd)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char *));
	if (read(fd, buffer, BUFFER_SIZE) <= 0)
		return (buffer);
	while (!ft_strchr(buffer, '\n'))
	{
		tmp = ft_calloc((BUFFER_SIZE + 1), sizeof(char *));
		if (read(fd, tmp, BUFFER_SIZE) <= 0)
		{
			free(tmp);
			break ;
		}
		buffer = ft_strjoin(buffer, tmp);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*storage[2048];
	char		*trashline;
	char		*line;
	int			i;

	trashline = ft_newline(fd);
	if ((!trashline && !storage[fd]) || (trashline[0] == '\0' && !storage[fd]))
	{
		free(trashline);
		return (NULL);
	}
	trashline = ft_strjoin(storage[fd], trashline);
	i = 0;
	while (trashline[i] != '\n' && trashline[i] != '\0')
		i++;
	line = ft_substr(trashline, 0, i + 1);
	if (trashline[i] == '\n')
		storage[fd] = ft_substr(trashline, i + 1, ft_strlen(trashline) - i - 1);
	else
		storage[fd] = NULL;
	free(trashline);
	return (line);
}
