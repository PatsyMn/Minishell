/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:19:33 by mbores            #+#    #+#             */
/*   Updated: 2025/06/26 13:15:24 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_and_return(int fd, const char *msg, int ret)
{
	if (fd != -1)
		close(fd);
	if (msg)
		perror(msg);
	return (ret);
}

void	exec_child(t_pipex *var, int i)
{
	int	out_fd;

	if (i < var->cmd_count - 1)
	{
		close(var->pipe_fd[0]);
		out_fd = var->pipe_fd[1];
	}
	else
		out_fd = var->outfile;
	execute_cmd(*var, var->argv[i + var->cmd_start], var->input_fd, out_fd);
}

int	pipe_and_fork(t_pipex *var, int i)
{
	if (i < var->cmd_count - 1 && pipe(var->pipe_fd) == -1)
		return (close_and_return(var->input_fd, "pipe error", -1));
	var->pid = fork();
	if (var->pid == -1)
	{
		if (i < var->cmd_count - 1)
		{
			close(var->pipe_fd[0]);
			close(var->pipe_fd[1]);
		}
		return (close_and_return(var->input_fd, "fork error", -1));
	}
	if (var->pid == 0)
		exec_child(var, i);
	return (var->pid);
}

void	close_all_fds(t_pipex *var)
{
	if (var->input_fd != -1 && var->input_fd != var->infile)
		close(var->input_fd);
	if (var->infile != -1 && var->infile != STDIN_FILENO)
		close(var->infile);
	if (var->outfile != -1 && var->outfile != STDOUT_FILENO)
		close(var->outfile);
}

pid_t	child_process(t_pipex var)
{
	int		i;

	var.input_fd = var.infile;
	var.last_pid = -1;
	i = 0;
	while (i < var.cmd_count)
	{
		if (pipe_and_fork(&var, i) == -1)
			return (-1);
		if (var.input_fd != var.infile && var.input_fd != -1)
			close(var.input_fd);
		if (i < var.cmd_count - 1)
		{
			close(var.pipe_fd[1]);
			var.input_fd = var.pipe_fd[0];
		}
		var.last_pid = var.pid;
		i++;
	}
	close_all_fds(&var);
	return (var.last_pid);
}
