/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/11 03:41:12 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_newline(int fd)
{
    char *buffer;
    char *tmp;

    buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char *));
    if (read(fd, buffer, BUFFER_SIZE) <= 0)
        return (buffer);
    while (!ft_strchr(buffer, '\n')) 
    {
        tmp = ft_calloc((BUFFER_SIZE + 1), sizeof(char *));
        if (read(fd, tmp, BUFFER_SIZE) <= 0)
        {
            free(tmp);
            break;
        }
        buffer = ft_strjoin(buffer, tmp);
        free(tmp);
    }
    return (buffer);
}

char *get_next_line(int fd)
{
    static char *storage = NULL;
    char *trashline;
    char *line;
    int i;

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

int main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *line;
  	int i = 0;
	while (i < 63)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		i++;
		printf("%s", line);
		free(line);
	}
	return (0);
}