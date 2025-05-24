/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:24:45 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/05/24 17:52:17 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*read_file(int	fd, char *buffer)
{
	char	*templine;
	size_t	i;
	ssize_t		r;

	while (buffer[i] =! '\n' || buffer[i] != '\0')
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r < 0)
		{
			free (buffer);
			return (NULL);
		}
		templine = ft_strjoin(templine, buffer);
	}
	return (templine);
}

static char	*extract_line(char	*templine)
{
	int	i;
	i = 0;

	while (templine[i] != '\n')
		i++;
	line = ft_substring(templine, 0 , i)

	return (line);

}
static char	*extract_leftover(char	*templine, char *buffer)
{
	int start;
	int	i;
	
	i = 0;

	while (templine[i])
	{
		while (templine[i] != '\n')
		{
			i++;
			start = i + 2;
		}
		i++;
	}
	buffer = ft_substring(templine, start , i)
	return (buffer);

}
char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*line;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == '\0')
		return (NULL);
	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	templine = read_file(fd, buffer);
	free (buffer);
	line = extract_line(templine);
	buffer = extract_leftover(templine);
	return (line);
}
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int fd;

	
	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd)
	return (0);
	

}