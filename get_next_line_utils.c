/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:25:36 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/05/25 13:29:50 by jkorvenp         ###   ########.fr       */
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
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
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
size_t	ft_strlcat(char *dst, const char *src, size_t size)
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
	ls = ft_strlen(src);
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


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_size;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1) + 1;
	size = s1_size + ft_strlen(s2);
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_size);
	ft_strlcat(dest, s2, size);
	return (dest);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
//	if (start > ft_strlen(s))
//		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, &s[start], len + 1);
	return (sub);
}