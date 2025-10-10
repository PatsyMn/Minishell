/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:37:20 by mbores            #+#    #+#             */
/*   Updated: 2025/10/10 12:41:31 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_in(t_pipex *pipex, t_token *token)
{
	if (token->type == T_REDIR_IN)
	{
		if (pipex->input_fd >= 0)
		{
			close(pipex->input_fd);
			pipex->input_fd = -1;
		}
		pipex->input_fd = open(token->next->value, O_RDONLY);
		if (pipex->input_fd == -1)
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, token->next->value,
				ft_strlen(token->next->value));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return (0);
		}
	}
	return (1);
}

static int	redir_out(t_pipex *pipex, t_token *token)
{
	if (token->type == T_REDIR_OUT)
	{
		if (pipex->output_fd >= 0)
		{
			close(pipex->output_fd);
			pipex->output_fd = -1;
		}
		pipex->output_fd = open(token->next->value, 
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->output_fd == -1)
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, token->next->value,
				ft_strlen(token->next->value));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return (0);
		}
	}
	return (1);
}

static int	redir_append(t_pipex *pipex, t_token *token)
{
	if (token->type == T_APPEND_OUT)
	{
		if (pipex->output_fd >= 0)
		{
			close(pipex->output_fd);
			pipex->output_fd = -1;
		}
		pipex->output_fd = open(token->next->value, 
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->output_fd == -1)
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, token->next->value,
				ft_strlen(token->next->value));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return (0);
		}
	}
	return (1);
}

static int	redir_heredoc(t_pipex * pipex, t_command *command, t_export *export)
{
	int	status;

	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		perror("fork heredoc");
		return (0);
	}
	if (pipex->pid == 0)
	{
		open_heredoc(command);
		free_execute(export, pipex);
		exit(0);
	}
	waitpid(pipex->pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 130;
		return (0);
	}
	return (1);
}

int	redirection(t_pipex *pipex, t_command *command, t_export *export)
{
	t_token *tok;

	tok = command->token_list;
	while (tok)
	{
		if (!redir_in(pipex, tok) || !redir_out(pipex, tok)
			|| !redir_append(pipex, tok))
			return (0);
		if (tok->type == T_HEREDOC)
		{
			if (!redir_heredoc(pipex, command, export))
				return (0);
			else
			{
				pipex->input_fd = open("temp", O_RDONLY);
				if (pipex->input_fd == -1)
				{
					perror("open heredoc_tmp");
					return (0);
				}
			}
		}
		tok = tok->next;
	}
	return (1);
}
