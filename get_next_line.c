/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/05 16:17:50 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(int fd)
{
	char	*buff;
	int		check;
	//ft_calloc
	buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char *));
	if (!buff)
		return (NULL);
	check = read(fd, buff, BUFFER_SIZE);
	if (check <= 0)
	{
		free(buff);
		return (NULL);
	}
	return(buff);
}

size_t	ft_jumpline_search(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*temp_line;


	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_getline(fd);
	if (!line)
		return (NULL);
	while (line[ft_jumpline_search(line)] != '\n')
	{
		temp_line = ft_getline(fd);
		if (!temp_line)
			return (NULL);
		line = ft_strjoin(line, temp_line);
		free(temp_line);
	}
	temp_line = line;
	line = ft_strchr(line, '\n') + 1;
	temp_line[ft_jumpline_search(temp_line)] = '\0';
	return(temp_line);
}

/* int main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *line;
 	int i = 0;
  while (i < 42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s\n", line);
		i++; 	
	}
} */