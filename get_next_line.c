/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:16:51 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/12 16:09:17 by erico-ke         ###   ########.fr       */
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
	static char	*storage = NULL;
	char		*trashline;
	char		*line;
	int			i;

	trashline = ft_newline(fd);
	if ((!trashline && !storage) || (trashline[0] == '\0' && !storage))
	{
		free(trashline);
		return (NULL);
	}
	trashline = ft_strjoin(storage, trashline);
	i = 0;
	while (trashline[i] != '\n' && trashline[i] != '\0')
		i++;
	line = ft_substr(trashline, 0, i + 1);
	if (trashline[i] == '\n')
		storage = ft_substr(trashline, i + 1, ft_strlen(trashline) - i - 1);
	else
		storage = NULL;
	free(trashline);
	return (line);
}

/* int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *r;
	int i = 0;
	while (i < 1000000)
	{
		r = get_next_line(fd);
		if (r)
		{
			printf("%s", r);
			free(r);
		}
		else
			break;
		i++;
	}
	close(fd);
	return 0;
}  */