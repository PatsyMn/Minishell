/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:32:18 by mbores            #+#    #+#             */
/*   Updated: 2025/06/26 12:04:22 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_error(int file)
{
	if (file < 0)
	{
		perror("Error opening temp heredoc file");
		return (1);
	}
	else
		return (0);
}

void	read_heredoc(char *limiter)
{
	char	*line;
	size_t	lim_len;
	int		temp_infile_fd;

	lim_len = ft_strlen(limiter);
	temp_infile_fd = open_temp_heredoc_file("infile");
	if (check_error(temp_infile_fd))
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, lim_len) == 0
			&& line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(temp_infile_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_infile_fd);
}
