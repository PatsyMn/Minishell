/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:28:09 by mbores            #+#    #+#             */
/*   Updated: 2025/10/06 13:53:16 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    read_heredoc(t_command_2 *command, char *delimiter, int heredoc_file_fd)
{
    char    *line;
    size_t  lim_len;

    lim_len = ft_strlen(delimiter);
    while (1)
    {
        setup_signals_heredoc();
        write(1, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break ;
        if (ft_strncmp(line, delimiter, lim_len) == 0
            && line[lim_len] == '\n')
            break ;
        write(heredoc_file_fd, line, ft_strlen(line));
        free(line);
    }
    free(line);
    close(heredoc_file_fd);
}

void    open_heredoc(t_command_2 *command)
{
    char    *delimiter;
    int     heredoc_file_fd;

    delimiter = find_token(command->tokens_list, T_DELIMITER);
    heredoc_file_fd = open("temp", 
        O_WRONLY | O_CREAT | O_TRUNC, 0644);
    read_heredoc(command, delimiter, heredoc_file_fd);
}

// void    open_files(t_command_2 *command)
// {
//     int *infile_fd;
//     int *outfile_fd;

//     if (find_token(command->tokens_list, T_HEREDOC))
//     {
//         open_heredoc(command);
//         infile_fd = open("temp", O_RDONLY);
//     }
//     if (find_token(command->tokens_list, T_REDIR_IN))
//         infile_fd = open_infiles_outfiles(command->tokens_list, T_REDIR_IN);
// }
