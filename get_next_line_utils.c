/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:12:58 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/10 22:20:36 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	int		i;

	res = malloc(nmemb * size);
	if (res == 0)
		return (NULL);
	i = 0;
	while (res[i])
	{
		res[i] = '\0';
		i++;
	}
	return ((void *) res);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)ft_calloc(size, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	free(s1);
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	return (ret);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	/* if (start >= s_len)
		return (ft_strdup("")); */
	if (len > s_len - start)
		len = s_len - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*(s + start) != '\0')
	{
		res[i] = *(s + start);
		i++;
		s++;
	}
	return (res);
}
