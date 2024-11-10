/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/10 22:19:28 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_jumpsearch(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (0);
		i++;
	}
	return (i);
}

char	*ft_getline(int fd)
{
	char	*buff;
	char	*temp;
	int		check;

	buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char *));
	if (!buff)
		return (NULL);
	check = read(fd, buff, BUFFER_SIZE);
	if (check < 0)
		return (NULL);
	while (ft_jumpsearch(buff))
	{
		temp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char *));
		if (!temp)
			return (NULL);
		check = read(fd, temp, BUFFER_SIZE);
		if (check < 0)
			return (NULL);
		buff = ft_strjoin(buff, temp);
		free(temp);
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*s_line;
	char		*line;
	int			i;

	s_line = ft_getline(fd);
	i = 0;
	while (s_line[i] && s_line[i] != '\n')
		i++;
	line = ft_substr(s_line, 0, i + 1);
	return (line);
}

int main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *line;
 	int i = 0;
  while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s\n", line);
		i++;
		free(line);
	}
}