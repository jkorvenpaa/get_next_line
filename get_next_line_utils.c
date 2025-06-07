/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:25:36 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/06 14:32:01 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = gnl_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	gnl_strlcpy(dup, s, len + 1);
	return (dup);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = gnl_strlen(src);
	i = 0;
	if (size == 0)
		return (srclen);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

size_t	gnl_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	ld = 0;
	while (dst[ld] && ld < size)
	{
		ld++;
	}
	ls = gnl_strlen(src);
	if (ld == size)
		return (size + ls);
	i = 0;
	while (src[i] && ld + i < size - 1)
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	s1_size;
	size_t	size;

	if (!s1 || !s2)
	{
		free (s1);
		return (NULL);
	}
	s1_size = gnl_strlen(s1) + 1;
	size = s1_size + gnl_strlen(s2);
	dest = malloc(sizeof(char) * size);
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	gnl_strlcpy(dest, s1, s1_size);
	gnl_strlcat(dest, s2, size);
	free (s1);
	return (dest);
}
