/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:16:51 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/19 15:59:44 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_newline(int fd)
{
	char	*buffer;
	char	*tmp;
	char	*result;
	ssize_t	bytes_read;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	result = NULL;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(result, buffer);
		if (!tmp)
			return (free(buffer), free(result), NULL);
		result = tmp;
		if (ft_strchr(result, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*tmp;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(storage), storage = NULL, NULL);
	tmp = ft_newline(fd);
	if (!tmp && !storage)
		return (NULL);
	if (tmp)
		storage = ft_strjoin(storage, tmp);
	free(tmp);
	if (!storage || storage[0] == '\0')
		return (free(storage), storage = NULL, NULL);
	i = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	line = ft_substr(storage, 0, i + (storage[i] == '\n'));
	tmp = ft_substr(storage, i + (storage[i] == '\n'), ft_strlen(storage) - i);
	free(storage);
	storage = tmp;
	return (line);
}

/* int main()
{
	int fd = open("only_nl.txt", O_RDONLY);
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