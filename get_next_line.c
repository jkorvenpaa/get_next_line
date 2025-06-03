/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:24:45 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/03 14:37:14 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;
	unsigned char	uc;

	uc = (unsigned char)c;
	str = (unsigned char *) s;
	i = 0;
	while (str[i])
	{
		if (str[i] == uc)
			return ((char *) &str[i]);
		i++;
	}
	if (uc == '\0')
		return ((char *) &str[i]);
	return (NULL);
}

static char	*read_file(int fd, char *buffer)
{
	char	*templine;
	ssize_t	r;

	if (ft_strchr(buffer, '\n'))
	{
		templine = ft_strdup(buffer);
		return (templine);
	}
	templine = ft_strdup(buffer);
	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r < 0)
			break ;
		buffer[r] = '\0';
		templine = gnl_strjoin(templine, buffer);
		if (r == 0)
		{
			if (templine[0] == '\0')
				break ;
			return (templine);
		}
		if (ft_strchr(buffer, '\n'))
			return (templine);
	}
	free(templine);
	return (NULL);
}

static char	*extract_line(char	*templine)
{
	char	*sub;
	size_t	len;

	len = 0;
	while (templine[len] != '\n' && templine[len])
		len++;
	len += 1;
	if (!templine)
		return (NULL);
	//if (ft_strlen(templine) < 0)
	//	return (ft_strdup(""));
	if (len > (ft_strlen(templine) - 0))
		len = ft_strlen(templine) - 0;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, &templine[0], len + 1);
	free(templine);
	return (sub);
}

static void	extract_buffer(char *buffer)
{
	char	*remainder;
	size_t	i;

	remainder = ft_strchr(buffer, '\n');
	if (!remainder)
		return ;
	remainder++;
	i = 0;
	while (i <= ft_strlen(remainder))
	{
		buffer[i] = remainder[i];
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buffer);
	if (!line)
		return (NULL);
	line = extract_line(line);
	extract_buffer(buffer);
	return (line);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
		
	if (argc < 2)
	{
		printf("%d", 1);
		return (1);
		
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free (line);
	}
	close(fd);
	return (0);
}*/

