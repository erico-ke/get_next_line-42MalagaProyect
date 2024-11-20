/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:02:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/20 17:05:35 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*ft_newline(int fd)
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
	static char	*s_s[2048];
	char		*tmp;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(s_s[fd]), s_s[fd] = NULL, NULL);
	tmp = ft_newline(fd);
	if (!tmp && !s_s[fd])
		return (NULL);
	if (tmp)
		s_s[fd] = ft_strjoin(s_s[fd], tmp);
	free(tmp);
	if (!s_s[fd] || s_s[fd][0] == '\0')
		return (free(s_s[fd]), s_s[fd] = NULL, NULL);
	i = 0;
	while (s_s[fd][i] != '\n' && s_s[fd][i] != '\0')
		i++;
	line = ft_substr(s_s[fd], 0, i + (s_s[fd][i] == '\n'));
	tmp = ft_substr(s_s[fd], i + (s_s[fd][i] == '\n'), ft_strlen(s_s[fd]) - i);
	free(s_s[fd]);
	s_s[fd] = tmp;
	return (line);
}
