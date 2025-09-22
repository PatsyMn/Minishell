/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:23:45 by mbores            #+#    #+#             */
/*   Updated: 2025/09/22 14:54:15 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    close_all_fds(t_pipex *pipex, t_command *command)
{
    if (command->infile && pipex->input_fd != -1
        && pipex->input_fd != command->infile_fd)
        close(pipex->input_fd);
    if (command->infile && command->infile_fd != STDIN_FILENO)
        close(command->infile_fd);
    if (command->outfile && command->outfile_fd != STDOUT_FILENO)
        close(command->outfile_fd);
}

void    exec_child(t_pipex *pipex, t_command *command, char **env_copy)
{
    int out_fd;

    open_files(command);

    if (command->next)
    {
        close(pipex->pipe_fd[0]);
        out_fd = pipex->pipe_fd[1];
    }
    else
        out_fd = command->outfile_fd;
    execute_cmd(env_copy, command, pipex, out_fd);
}

int pipe_and_fork(t_pipex *pipex, t_command *command, char **env_copy)
{
    if (command->next && pipe(pipex->pipe_fd) == -1)
        return (-1);
    pipex->pid = fork();
    if (pipex->pid == -1)
    {
        if (command->next)
        {
            close(pipex->pipe_fd[0]);
            close(pipex->pipe_fd[1]);
        }
        return (-1);
    }
    if (!pipex->pid)
    {
        if (command->next)
            close(pipex->pipe_fd[0]);
        exec_child(pipex, command, env_copy);
    }
    else
    {
        if (command->next)
            close(pipex->pipe_fd[1]);
    }
    return (pipex->pid);
}

void    child_process(t_command *command, t_pipex *pipex, char **env_copy)
{
    if (command->infile)
        pipex->input_fd = command->infile_fd;
    pipex->last_pid = -1;
    pipex->cmd_count = 0;
    while (1)
    {
        if (pipe_and_fork(pipex, command, env_copy) == -1)
        {
            pipex->last_pid = -1;
            return ;
        }
        if (command->infile && pipex->input_fd != command->infile_fd
            && pipex->input_fd != -1)
            close(pipex->input_fd);
        if (command->next)
        {
            close(pipex->pipe_fd[1]);
            pipex->input_fd = pipex->pipe_fd[0];
        }
        pipex->last_pid = pipex->pid;
        if (!command->next)
            break ;
        command = command->next;
    }
    close_all_fds(pipex, command);
}
