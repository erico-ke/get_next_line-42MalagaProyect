/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/10/23 19:22:32 by erico-ke         ###   ########.fr       */
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
	if (n_switch == 1)
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
//quizas sea necesaria una funcion para liberar memorias en caso de error, si no se deberia agregar 
//if(!variable){free(variables);return (NULL);} en muchos lados

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_second_part;
	int			end_check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_line(fd);
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
