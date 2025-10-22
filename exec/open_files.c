/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:28:09 by mbores            #+#    #+#             */
/*   Updated: 2025/10/22 18:25:36 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_heredoc(char *delimiter, int heredoc_file_fd)
{
	char	*line;
	size_t	lim_len;

	lim_len = ft_strlen(delimiter);
	init_signals_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_status == 99)
		{
			printf("\n");
			if (line)
				free(line);
			break ;
		}
		if (ft_strncmp(line, delimiter, lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(heredoc_file_fd, line, ft_strlen(line));
		free(line);
	}
}

void	open_heredoc(t_command *command, t_pipex *pipex)
{
	char	*delimiter;
	int		heredoc_file_fd;

	g_status = 0;
	delimiter = find_delimiter(&command->token_list);
	if (!delimiter)
		return ;
	heredoc_file_fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_file_fd == -1)
	{
		perror("open heredoc");
		return ;
	}
	read_heredoc(delimiter, heredoc_file_fd);
	free(delimiter);
	close(heredoc_file_fd);
	init_signals_prompt();
	if (g_status == 99 || g_status == 130)
	{
		unlink("temp");
		g_status = 130;
		dup2(pipex->saved_stdin, STDIN_FILENO);
		return ;
	}
}
