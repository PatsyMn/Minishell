/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:28:09 by mbores            #+#    #+#             */
/*   Updated: 2025/10/02 16:51:50 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    read_heredoc(t_command *command)
{
    char    *line;
    size_t  lim_len;

    lim_len = ft_strlen(command->limiter);
    while (1)
    {
        setup_signals_heredoc();
        write(1, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break ;
        if (ft_strncmp(line, command->limiter, lim_len) == 0
            && line[lim_len] == '\n')
            break ;
        write(command->heredoc_file_fd, line, ft_strlen(line));
        free(line);
    }
    free(line);
    close(command->heredoc_file_fd);
}

static void    open_heredoc(t_command *command)
{
    if (!command->infile)
        return ;
    command->limiter = command->infile;
    command->heredoc_file_fd = open("temp",
        O_WRONLY | O_CREAT | O_TRUNC, 0644);
    read_heredoc(command);
}

void    open_files(t_command *command)
{
    if (command->heredoc)
    {
        open_heredoc(command);
        command->infile_fd = open("temp", O_RDONLY);
    }
    else if (command->infile)
        command->infile_fd = open(command->infile, O_RDONLY);
    if (command->append && command->outfile)
        command->outfile_fd = open(command->outfile,
            O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (command->outfile)
    {
        command->outfile_fd = open(command->outfile,
            O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (command->outfile_fd == -1)
            perror("open outfile");
    }
}
