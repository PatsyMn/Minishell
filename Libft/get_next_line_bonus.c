/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:18:08 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/05/01 15:30:53 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_fillbuf_w_tmp(char *buffer, int fd)
{
	char	*temp;
	int		bytes_read;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*ft_extract_first_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_remove_first_line(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (gnl_strlen(buffer) - i + 1));
	if (new_buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffers[LIMIT_FD_OPEN];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= LIMIT_FD_OPEN)
	{
		if (buffers[fd])
		{
			free(buffers[fd]);
			buffers[fd] = NULL;
		}
		return (NULL);
	}
	buffers[fd] = ft_fillbuf_w_tmp(buffers[fd], fd);
	if (!buffers[fd])
		return (NULL);
	line = ft_extract_first_line(buffers[fd]);
	buffers[fd] = ft_remove_first_line(buffers[fd]);
	if (!buffers[fd] && gnl_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// #include <stdio.h>

// int main()
// {
// 	char *line;
// 	int fd1 = open("petit_prince.txt", O_RDONLY);
// 	int fd2 = open("mdc.txt", O_RDONLY);
// 	int fd3 = open("README.md", O_RDONLY);
// 	while ((line = get_next_line(fd1)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd1);
// while ((line = get_next_line(fd2)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd2);
// while((line = get_next_line(fd3)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd2);
// }