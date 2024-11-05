/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/05 01:13:05 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(int fd)
{
	void	*buff;
	int		check;
	
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	check = read(fd, buff, BUFFER_SIZE);
	if (check < 0)
		return (NULL);
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
	char		*aux;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_getline(fd);
	while (line[ft_jumpline_search(line)] != '\n')
	{
		temp_line = ft_getline(fd);
		line = ft_strjoin(line, temp_line);
	}
	aux = line;
	line = ft_strchr(line, '\n') + 1;
	ft_strlcpy(temp_line, aux, ft_jumpline_search(aux) + 1);
	return(temp_line);
}

/* int main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s\n\n\n\n", line);
	int i = 0;
	while (i < 9)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		i++; 	
	}
} */