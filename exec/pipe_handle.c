/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:23:45 by mbores            #+#    #+#             */
/*   Updated: 2025/10/14 17:20:21 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child(t_pipex *pipex, t_command *command, t_export *export)
{
    if (pipex->output_fd >= 0)
        dup2(pipex->output_fd, STDOUT_FILENO);
    else if (command->next)
        dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    if (pipex->input_fd >= 0)
        dup2(pipex->input_fd, STDIN_FILENO);
    else if (pipex->cmd_count > 0 && pipex->pipe_fd[0] >= 0)
        dup2(pipex->pipe_fd[0], STDIN_FILENO);
    safe_close(&pipex->pipe_fd[0]);
    safe_close(&pipex->pipe_fd[1]);
    safe_close(&pipex->input_fd);
    safe_close(&pipex->output_fd);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (is_builtin(command))
        g_status = execute_builtin(command, export, pipex);
    else
        g_status = execute_cmd(export, command, pipex);
    exit(g_status);
}

static int	create_pipe_if_needed(t_pipex *pipex, t_command *command)
{
	if (command->next && pipex->output_fd == -1)
	{
		if (pipe(pipex->pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	else
	{
		pipex->pipe_fd[0] = -1;
		pipex->pipe_fd[1] = -1;
	}
	return (0);
}

static int	fork_and_exec(t_pipex *pipex, t_command *command, t_export *export)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
        exec_child(pipex, command, export);
    pipex->pid = pid;
    return (0);
}

static void	exec_pipeline(t_command *commands, t_pipex *pipex, t_export *export)
{
	t_command	*cmd;
	int			status;

    cmd = commands;
    while (cmd)
    {
        if (!redirection(pipex, cmd, export))
        {
            safe_close(&pipex->pipe_fd[0]);
            safe_close(&pipex->pipe_fd[1]);
            return;
        }
        if (create_pipe_if_needed(pipex, cmd) == -1)
            return ;
        if (fork_and_exec(pipex, cmd, export) == -1)
        {
            safe_close(&pipex->pipe_fd[0]);
            safe_close(&pipex->pipe_fd[1]);
            return;
        }
        if (pipex->input_fd >= 0)
            safe_close(&pipex->input_fd);
        if (pipex->pipe_fd[1] >= 0)
        {
            safe_close(&pipex->pipe_fd[1]);
            pipex->input_fd = pipex->pipe_fd[0];
            pipex->pipe_fd[0] = -1;
        }
        cmd = cmd->next;
        pipex->cmd_count++;
    }
    while (wait(&status) > 0)
        handle_child_status(status);
}

static int	restore_prompt(t_pipex *pipex)
{
    if (pipex->output_fd >= 0)
    {
        dup2(pipex->saved_stdout, STDOUT_FILENO);
        safe_close(&pipex->saved_stdout);
    }
    if (pipex->input_fd >= 0)
    {
        dup2(pipex->saved_stdin, STDIN_FILENO);
        safe_close(&pipex->saved_stdin);
    }
    safe_close(&pipex->input_fd);
    safe_close(&pipex->output_fd);
    return (0);
}

static int	is_pipe(t_command *commands, t_pipex *pipex, t_export *export)
{
	if (!commands->next && is_builtin(commands))
	{
		if (redirection(pipex, commands, export))
		{
			if (pipex->output_fd != -1)
				dup2(pipex->output_fd, STDOUT_FILENO);
			if (pipex->input_fd != -1)
				dup2(pipex->input_fd, STDIN_FILENO);
			g_status = execute_builtin(commands, export, pipex);
		}
		return (0);
	}
	return (1);
}

int	child_process(t_command *commands, t_pipex *pipex, t_export *export)
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
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
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
