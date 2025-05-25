/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:24:45 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/05/25 14:55:16 by jkorvenp         ###   ########.fr       */
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
		{
			return ((char *) &str[i]);
		}
		i++;
	}
	if (uc == '\0')
		return ((char *) &str[i]);
	return (NULL);
}
static char	*read_file(int	fd, char *buffer)
{
	char	*templine;
	ssize_t		r;

	templine = malloc(sizeof(char)* BUFFER_SIZE + 1);
	if (!templine)
		return NULL;
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0 && !ft_strchr(buffer, '\n'))
	{	
		templine = ft_strjoin(templine, buffer);
		r = read(fd, buffer, BUFFER_SIZE);
	}
	if (r < 0)
	{
		free (templine);
		return (NULL);
	}
	return (templine);
}

static char	*extract_line(char	*templine)
{
	char	*line;
	int	i;
	i = 0;

	while (templine[i] != '\n')
		i++;
	line = ft_substr(templine, 0 , i + 1);
	return (line);

}
static char	*extract_leftover(char *buffer)
{
	int start;
	int	i;
	
	i = 0;

	while (buffer[i])
	{
		while (buffer[i] != '\n')
		{
			i++;
			start = i + 2;
		}
		i++;
	}
	buffer = ft_substr(buffer, start , i);
	return (buffer);

}
char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL); 
	line = extract_line(buffer);
	buffer = extract_leftover(buffer);
	return (line);
}
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd;
	char	*line;
	
	if (argc < 2)
	{
		printf("%d", 1);
		return (1);
		
	}
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd);
	}
	free (line);
	close(fd);
	return (0);

}