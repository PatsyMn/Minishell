/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:39:12 by mbores            #+#    #+#             */
/*   Updated: 2025/10/24 14:49:11 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_close(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

char	*find_delimiter(t_token **token_list)
{
	t_token	*prev;
	t_token	*cur;
	char	*value;

	prev = NULL;
	cur = *token_list;
	while (cur)
	{
		if (cur->type == T_DELIMITER)
		{
			value = ft_strdup(cur->value);
			if (prev)
				prev->next = cur->next;
			else
				*token_list = cur->next;
			free(cur->value);
			free(cur);
			return (value);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

int	restore_prompt(t_pipex *pipex)
{
	if (pipex->output_fd >= 0)
		dup2(pipex->saved_stdout, STDOUT_FILENO);
	if (pipex->input_fd >= 0)
		dup2(pipex->saved_stdin, STDIN_FILENO);
	safe_close(&pipex->input_fd);
	safe_close(&pipex->output_fd);
	safe_close(&pipex->saved_stdout);
	safe_close(&pipex->saved_stdin);
	return (0);
}

int	is_pipeline(t_command *commands, t_pipex *pipex, t_export *export)
{
	if (!commands->next && is_builtin(commands))
	{
		if (redirection(pipex, commands))
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

int	check_pipe(t_pipex *pipex, t_command *command, t_export *export)
{
	if (fork_and_exec(pipex, command, export) == -1)
	{
		safe_close(&pipex->pipe_fd[0]);
		safe_close(&pipex->pipe_fd[1]);
		return (0);
	}
	if (pipex->input_fd >= 0)
		safe_close(&pipex->input_fd);
	if (pipex->pipe_fd[1] >= 0)
	{
		safe_close(&pipex->pipe_fd[1]);
		pipex->input_fd = pipex->pipe_fd[0];
		pipex->pipe_fd[0] = -1;
	}
	return (1);
}
