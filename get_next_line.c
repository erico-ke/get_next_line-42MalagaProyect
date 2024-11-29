/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:16:51 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/29 14:54:16 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_read(int fd, char *backup)
{
	int		check_read;
	char	*buf;

	buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	check_read = 1;
	while (!(ft_strchr(backup, '\n')) && check_read != 0)
	{
		check_read = read(fd, buf, BUFFER_SIZE);
		if (check_read < 0)
		{
			free(buf);
			free(backup);
			return (NULL);
		}
		buf[check_read] = 0;
		backup = ft_strjoin(backup, buf);
	}
	free(buf);
	return (backup);
}

static char	*ft_get_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (backup[0] == 0)
		return (NULL);
	while (backup[i] && (backup[i] != '\n'))
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && (backup[i] != '\n'))
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_get_rest(char *backup)
{
	int		i;
	int		rest_i;
	char	*rest;

	i = 0;
	while (backup[i] && (backup[i] != '\n'))
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!rest)
	{
		free(rest);
		return (NULL);
	}
	++i;
	rest_i = 0;
	while (backup[i])
		rest[rest_i++] = backup[i++];
	rest[rest_i] = '\0';
	free(backup);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = ft_get_read(fd, backup);
	if (!backup)
		return (NULL);
	line = ft_get_line(backup);
	backup = ft_get_rest(backup);
	return (line);
}

/* int main()
{
	int fd = open("only_nl.txt", O_RDONLY);
	char *r;
	r = get_next_line(fd);
	while (r)
	{
		free(r);
		r = get_next_line(fd);
		printf("%s", r);

	}
	close(fd);
	return 0;
}  */