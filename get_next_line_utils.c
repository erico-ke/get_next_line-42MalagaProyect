/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:12:58 by erico-ke          #+#    #+#             */
/*   Updated: 2024/11/05 16:17:23 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dst[j] && j < size)
		j++;
	i = j;
	while (src[j - i] && j + 1 < size)
	{
		dst[j] = src[j - i];
		j++;
	}
	if (i < size)
		dst[j] = '\0';
	return (i + ft_strlen(src));
}

/* size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
} */

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(nmemb * size);
	if (res == 0)
		return (NULL);
	while (i < size)
	{
		res[i] = '\0';
		i++;
	}
	return ((void *) res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)ft_calloc(size, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < size - 1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	free(s1);
	ft_strlcat(ret, s2, size);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *) &s[i]);
	return (NULL);
}
