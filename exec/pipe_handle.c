/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:23:45 by mbores            #+#    #+#             */
/*   Updated: 2025/10/08 12:15:05 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    exec_child(t_pipex *pipex, t_command *command, t_export *export)
{
    if (pipex->output_fd != -1)
        dup2(pipex->output_fd, STDOUT_FILENO);
    else if (command->next)
        dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    if (pipex->input_fd != -1)
        dup2(pipex->input_fd, STDIN_FILENO);
    else if (pipex->cmd_count > 0)
        dup2(pipex->pipe_fd[0], STDIN_FILENO);
    if (pipex->pipe_fd[0] != -1)
        close(pipex->pipe_fd[0]);
    if (pipex->pipe_fd[1] != -1)
        close(pipex->pipe_fd[1]);
    g_status = execute_builtin(command, export);
    if (g_status == -1)
        g_status = execute_cmd(export->env, command);
}

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
        {
            if (!pipex->cmd_count)
                close(pipex->pipe_fd[0]);
            if (!command->next)
                close(pipex->pipe_fd[1]);
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            exec_child(pipex, command, export);
        }
    }
    return (0);
}

static void exec_pipeline(t_command *commands, t_pipex *pipex, t_export *export)
{
    t_command *cmd;
    int status;

    cmd = commands;
    while (cmd)
    {
        if (create_pipe_if_needed(pipex, cmd) == -1)
            return ;
        if (fork_and_exec(pipex, cmd, export) == -1)
            return ;
        if (pipex->input_fd != -1)
        {
            close(pipex->input_fd);
            pipex->input_fd = -1;
        }
        if (cmd->next)
        {
            close(pipex->pipe_fd[1]);
            pipex->input_fd = pipex->pipe_fd[0];
        }
        else
        {
            close(pipex->pipe_fd[0]);
            close(pipex->pipe_fd[1]);
        }
        pipex->last_pid = pipex->pid;
        pipex->cmd_count++;
        cmd = cmd->next;
    }
    while (wait(&status) > 0)
        handle_child_status(status);
}

static int restore_prompt(t_pipex * pipex)
{
    if (pipex->output_fd != -1)
    {
        close(pipex->output_fd);
        if (dup2(pipex->saved_stdout, STDOUT_FILENO) == -1)
        {
            perror("dup2 restore");
            return (1);
        }
        close(pipex->saved_stdout);
    }
    if (pipex->input_fd != -1)
    {
        close(pipex->input_fd);
        if (dup2(pipex->saved_stdin, STDIN_FILENO) == -1)
        {
            perror("dup2 restore");
            return (1);
        }
        close(pipex->saved_stdin);
    }
    return (0);
}

static int  is_pipe(t_command *commands, t_pipex *pipex, t_export *export)
{
    if (!commands->next && is_builtin(commands))
    {
        if (redirection(pipex, commands))
            g_status = execute_builtin(commands, export);
        return (0);
    }
    pipex->pid = fork();
    if (pipex->pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pipex->pid == 0)
    {
        if (redirection(pipex, commands))
            exec_child(pipex, commands, export);
    }
    return (0);
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
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (!is_pipe(commands, pipex, export))
    {
        restore_prompt(pipex);
        return (1);
    }
    exec_pipeline(commands, pipex, export);
    restore_prompt(pipex);
    return (1);
}
