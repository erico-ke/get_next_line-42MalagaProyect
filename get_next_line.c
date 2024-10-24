/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/10/24 14:57:09 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*ft_read_line(int fd)
{
	char	*buff;
	int		read_lines;

	buff = (char *) malloc (sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_lines = read(fd, buff, BUFFER_SIZE);
	if (read_lines < 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}
//Modificar, la devolucion de -1 no es util en el caso del join a menos que se agregue una condicion extra en la f_principal
//Hay que manejar el resto de la funcion post join, guardar el resto de la linea.

int	ft_full_line_check(char *line, int n_switch)
{
	int	i;

	i = 0;
	if (n_switch == -1)
	{
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\0')
			return (-1);
	}
	else if (n_switch == -2)
		while (line[i])
			i++;
	else
		while (line[i] && line[i] != '\n')
			i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(s1) + ft_full_line_check(s2, 0) + 1;
	ret = (char *) malloc(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, size);
	free(s1);
	ft_strlcat(ret, s2, size);
	if (ft_full_line_check(s2, -1) == -1)
		free(s2);
	/* Deleted s2 free, need to save the rest of the array if necesary */
	return (ret);
}

//quizas sea necesaria una funcion para liberar memorias en caso de error, si no se deberia agregar 
//if(!variable){free(variables);return (NULL);} en muchos lados

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_second_part;
	int			end_check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line_second_part)
		line = ft_read_line(fd);
	else
		{
			line = /* función que copie la parte restante de la linea que esta en alguna parte de line_second_part */;
			line_second_part = NULL;
		}
	while (ft_full_line_check(line, 1) == -1)
	{
		line_second_part = ft_read_line(fd);
		end_check = ft_full_line_check(line_second_part, -2);
		line = ft_strjoin(line, line_second_part);
		if (end_check < BUFFER_SIZE)
			break ;
	}
	return (line);
}
