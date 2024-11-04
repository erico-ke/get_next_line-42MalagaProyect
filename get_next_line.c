/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:12 by erico-ke          #+#    #+#             */
/*   Updated: 2024/10/29 17:12:01 by erico-ke         ###   ########.fr       */
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
	read_lines = read(fd, buff, 1);
	if (read_lines < 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

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

	size = ft_strlen(s1, 0) + ft_full_line_check(s2, 0) + 1;
	ret = (char *) malloc(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, size);
	//free(s1); 
	ft_strlcat(ret, s2, size);
	/* if (!(ft_full_line_check(s2, -1) == -1))
		free(s2); */
	return (ret);
}

char	*line_cutter(char *to_cut, int n_switch)
{
	char	*c_l;
	int		to_cut_len_one;
	int		to_cut_len_cero;

	to_cut_len_one = ft_strlen(to_cut, 1);
	to_cut_len_cero = ft_strlen(to_cut + to_cut_len_one, 0);
	if (n_switch == 0)
	{
		c_l = (char *) malloc (to_cut_len_one + 1);
		ft_strlcpy(c_l, to_cut, to_cut_len_one + 1);
		free(to_cut);
	}
	if (n_switch == 1)
	{
		c_l = (char *) malloc (to_cut_len_cero + 1);
		ft_strlcpy(c_l, to_cut + to_cut_len_one, to_cut_len_cero + 1);
		free(to_cut);
	}
	return (c_l);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_second_part;
	int			end_check;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line_second_part)
		line = ft_read_line(fd);
	else
		line = line_cutter(line_second_part, 1);
	i = 0;
	/* condicion para saber cuando termina la linea(salto de linea o nulo) */
	while (line[i] != '\n')
	{
		line_second_part = ft_read_line(fd);
		end_check = ft_full_line_check(line_second_part, -2);
		line = ft_strjoin(line, line_second_part);
		if (end_check < BUFFER_SIZE)
			break ;
		i ++;
	}
	return (line);
}

int main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s\n", line);
}