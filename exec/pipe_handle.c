/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:23:45 by mbores            #+#    #+#             */
/*   Updated: 2025/10/06 17:55:40 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    close_all_fds(t_pipex *pipex, t_command *command)
// {
//     if (command->infile && pipex->input_fd != -1
//         && pipex->input_fd != command->infile_fd)
//         close(pipex->input_fd);
//     if (command->infile && command->infile_fd != STDIN_FILENO)
//         close(command->infile_fd);
//     if (command->outfile && command->outfile_fd != STDOUT_FILENO)
//         close(command->outfile_fd);
//     if (dup2(pipex->saved_stdin, STDIN_FILENO) == -1
//         || dup2(pipex->saved_stdout, STDOUT_FILENO) == -1)
//     {
//         perror("dup2 restore");
//         exit(1);
//     }
//     close(pipex->saved_stdin);
//     close(pipex->saved_stdout);
// }

void    exec_child(t_pipex *pipex, t_command *command, t_export *export)
{
    if (!pipex->cmd_count)
        close(pipex->pipe_fd[0]);
    if (!command->next)
        close(pipex->pipe_fd[1]);
    if (pipex->output_fd != -1)
        dup2(pipex->output_fd, STDOUT_FILENO);
    else if (!command->next)
        dup2(pipex->saved_stdout, STDOUT_FILENO);
    else
        dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    if (pipex->input_fd != -1)
        dup2(pipex->input_fd, STDIN_FILENO);
    else if (!pipex->cmd_count)
        dup2(pipex->saved_stdin, STDIN_FILENO);
    else
        dup2(pipex->pipe_fd[0], STDIN_FILENO);
    g_status = execute_builtin(command, export);
    if (g_status == -1)
        g_status = execute_cmd(export->env, command);
}

// void    exec_child(t_pipex *pipex, t_command_2 *command, t_export *export)
// {
//     open_files(command);
//     if (pipex->cmd_count > 0)
//         dup2(pipex->input_fd, STDIN_FILENO);
//     else if (command->infile_fd != -1)
//         dup2(command->infile_fd, STDIN_FILENO);
//     if (command->next)
//         dup2(pipex->pipe_fd[1], STDOUT_FILENO);
//     else if (command->outfile_fd != -1)
//         dup2(command->outfile_fd, STDOUT_FILENO);
//     if (pipex->pipe_fd[0] != -1)
//         close(pipex->pipe_fd[0]);
//     if (pipex->pipe_fd[1] != -1)
//         close(pipex->pipe_fd[1]);
//     if (pipex->input_fd != -1)
//         close(pipex->input_fd);
//     if (command->infile_fd > 2)
//         close(command->infile_fd);
//     if (command->outfile_fd > 2)
//         close(command->outfile_fd);
//     g_status = execute_builtin(command, export);
//     if (g_status == -1)
//         g_status = execute_cmd(export->env, command);
// }

static int create_pipe_if_needed(t_pipex *pipex, t_command *command)
{
    if (command->next && pipe(pipex->pipe_fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    return (0);
}

static int fork_and_exec(t_pipex *pipex, t_command *command, t_export *export)
{
    pipex->pid = fork();
    if (pipex->pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pipex->pid == 0)
    {
        if (redirection(pipex, command))
            exec_child(pipex, command, export);
    }
    return (0);
}

// static void update_parent_fds(t_pipex *pipex, t_command_2 *command)
// {
//     if (pipex->input_fd != -1 && pipex->input_fd != command->infile_fd)
//         close(pipex->input_fd);
//     if (command->next)
//     {
//         close(pipex->pipe_fd[1]);
//         pipex->input_fd = pipex->pipe_fd[0];
//     }
//     pipex->last_pid = pipex->pid;
// }

static void exec_pipeline(t_command *commands, t_pipex *pipex, t_export *export)
{
    while (commands)
    {
        if (create_pipe_if_needed(pipex, commands) == -1)
            return ;
        if (fork_and_exec(pipex, commands, export) == -1)
            return ;
        pipex->last_pid = pipex->pid;
        // update_parent_fds(pipex, commands);
        if (!commands->next)
            break ;
        commands = commands->next;
        pipex->cmd_count++;
    }
}

static void restore_prompt(t_pipex * pipex)
{
    if (pipex->output_fd != -1)
    {
        close(pipex->output_fd);
        if (dup2(pipex->saved_stdout, STDOUT_FILENO) == -1)
        {
            perror("dup2 restore");
            exit(1);
        }
        close(pipex->saved_stdout);
    }
    if (pipex->input_fd != -1)
    {
        close(pipex->input_fd);
        if (dup2(pipex->saved_stdin, STDIN_FILENO) == -1)
        {
            perror("dup2 restore");
            exit(1);
        }
        close(pipex->saved_stdin);
    }
}

static int  is_pipe(t_command *commands, t_pipex *pipex, t_export *export)
{
    if (!commands->next)
    {
        if (redirection(pipex, commands))
        {
            exec_child(pipex, commands, export);
            restore_prompt(pipex);
        }
        return (0);
    }
    return (1);
}

int child_process(t_command *commands, t_pipex *pipex, t_export *export)
{
    pipex->saved_stdin = dup(STDIN_FILENO);
    pipex->saved_stdout = dup(STDOUT_FILENO);
    if (pipex->saved_stdin == -1 || pipex->saved_stdout == -1)
    {
        perror("dup");
        exit(1);
    }
    pipex->input_fd = -1;
    pipex->output_fd = -1;
    pipex->cmd_count = 0;
    pipex->last_pid = -1;
    if (!is_pipe(commands, pipex, export))
        return (1);
    exec_pipeline(commands, pipex, export);
    restore_prompt(pipex);
    return (1);
}

// int pipe_and_fork(t_pipex *pipex, t_command *command, t_export *export)
// {
//     open_files(command);
//     if (command->next && pipe(pipex->pipe_fd) == -1)
//         return (-1);
//     pipex->pid = fork();
//     if (pipex->pid == -1)
//     {
//         if (command->next)
//         {
//             close(pipex->pipe_fd[0]);
//             close(pipex->pipe_fd[1]);
//         }
//         return (-1);
//     }
//     if (!pipex->pid)
//     {
//         if (command->next)
//             close(pipex->pipe_fd[0]);
//         exec_child(pipex, command, export);
//     }
//     else
//     {
//         if (command->next)
//             close(pipex->pipe_fd[1]);
//     }
//     return (pipex->pid);
// }

// void    child_process(t_command *command, t_pipex *pipex, t_export *export)
// {
//     if (command->infile)
//         pipex->input_fd = command->infile_fd;
//     pipex->last_pid = -1;
//     pipex->cmd_count = 0;
//     while (1)
//     {
//         if (pipe_and_fork(pipex, command, export) == -1)
//         {
//             perror("fork");
//             pipex->last_pid = -1;
//             return ;
//         }
//         if (command->infile && pipex->input_fd != command->infile_fd
//             && pipex->input_fd != -1)
//             close(pipex->input_fd);
//         if (command->next)
//         {
//             close(pipex->pipe_fd[1]);
//             pipex->input_fd = pipex->pipe_fd[0];
//         }
//         pipex->last_pid = pipex->pid;
//         if (!command->next)
//             break ;
//         command = command->next;
//     }
// }
