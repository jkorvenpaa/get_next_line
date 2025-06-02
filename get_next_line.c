/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:24:45 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/02 17:50:55 by jkorvenp         ###   ########.fr       */
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
			i++;
			return ((char *) &str[i]);
		}
		i++;
	}
	if (uc == '\0')
		return ((char *) &str[i]);
	return (NULL);
}
#include <stdio.h>

static char	*read_file(int	fd, char *buffer)
{
	char	*templine;
	ssize_t		r;

	if (ft_strchr(buffer, '\n'))
		return (buffer);
	
	templine = malloc(1);
	if (!templine)
		return NULL;
	templine [0] = '\0';
	templine = gnl_strjoin(templine, buffer);
	
	//templine = ft_strdup(buffer);
	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			break;
		buffer[r] = '\0';
		templine = gnl_strjoin(templine, buffer);
		if (r == 0 && templine[0] != '\0')
			return(templine);
		if (ft_strchr(buffer, '\n'))
			return (templine);
			
	}
	//buffer = ft_strdup(templine);
	free(templine);
	return (NULL);
}

static char	*extract_line(char	*templine)
{
	char	*line;
	int	i;
	i = 0;

	while (templine[i] != '\n' && templine[i])
		i++;
	line = ft_substr(templine, 0 , i + 1);
	return (line);

}
/*
static char	*extract_leftover(char *buffer)
{
	int start;
	int	i;
	
	i = 0;
	start = 0;

	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			start = i;
			break;
		}
		i++;
	}
	i = ft_strlen(buffer);
	buffer = ft_substr(buffer, start , i - start);
	return (buffer);
}
*/
void	extract_leftover(char *buffer)
{
	char	*remainder;

	size_t	i;

	remainder = ft_strchr(buffer, '\n');
	if (!remainder)
		return;
	i = 0;
	while (i <= ft_strlen(remainder))
	{
		buffer[i] = remainder[i];
		i++;
	}
}
/*
void	extract_leftover(char *buffer)
{
	int start;
	int	i;
	
	i = 0;
	start = 0;

	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			start = i;
			break;
		}
		i++;
	}
	i = ft_strlen(buffer);
	buffer = ft_substr(buffer, start , i - start);
}
*/

char	*get_next_line(int fd)
{
	//static char	*buffer;
	static char	buffer[BUFFER_SIZE + 1];
	char	*line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	/*
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[BUFFER_SIZE + 1] = '\0';
	}
	*/
	//buffer = read_file(fd, buffer);
	line = read_file(fd, buffer);
	if (!line)//(!buffer)
		return (NULL);
	line = extract_line(line);
	//line = extract_line(buffer);
	//buffer = extract_leftover(buffer);
	//line = extract_leftover(buffer);
	extract_leftover(buffer);
	return (line);
}
#include <fcntl.h>
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
		printf("%s", line);
		if (!line)
			break ;
		free (line);
	}
	/*	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);*/
	close(fd);
	return (0);
}
