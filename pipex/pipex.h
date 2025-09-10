/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:46:39 by mbores            #+#    #+#             */
/*   Updated: 2025/06/30 13:15:15 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/GNL/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	int		cmd_count;
	int		cmd_start;
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	int		input_fd;
	pid_t	pid;
	pid_t	last_pid;
}			t_pipex;

void		execute_cmd(t_pipex var, char *cmd_str, int fd_in, int fd_out);
pid_t		child_process(t_pipex var);
void		read_heredoc(char	*limiter);
int			open_temp_heredoc_file(char *file_name);

#endif