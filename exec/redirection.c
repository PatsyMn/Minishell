/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:37:20 by mbores            #+#    #+#             */
/*   Updated: 2025/10/06 14:49:26 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_in(t_pipex * pipex, t_token *token)
{
	if (token->type == T_REDIR_IN)
	{
		if (pipex->input_fd)
			close(pipex->input_fd);
		pipex->input_fd = open(token->next->value, O_RDONLY);
		if (pipex->input_fd == -1)
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, token->next->value,
				ft_strlen(token->next->value));
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			return (0);
		}
		return (1);
	}
	return (1);
}

static int	redir_out(t_pipex *pipex, t_token *token)
{
	if (token->type == T_REDIR_OUT)
	{
		if (pipex->output_fd)
			close(pipex->output_fd);
		pipex->output_fd = open(token->next->value, 
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->output_fd == -1)
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, token->next->value,
				ft_strlen(token->next->value));
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			return (0);
		}
		return (1);
	}
	return (1);
}

static int	redir_append(t_pipex *pipex, t_token *token)
{
	if (token->type == T_APPEND_OUT)
	{
		if (pipex->output_fd)
			close(pipex->output_fd);
		pipex->output_fd = open(token->next->value, 
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->output_fd == -1)
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, token->next->value,
				ft_strlen(token->next->value));
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			return (0);
		}
		return (1);
	}
	return (1);
}

int	redirection(t_pipex *pipex, t_command_2 *command)
{
	while (command->tokens_list)
	{
		if (redir_in(pipex, command->tokens_list)
			&& redir_out(pipex, command->tokens_list)
			&& redir_append(pipex, command->tokens_list))
			return (0);
		if (command->tokens_list->type == T_HEREDOC)
			open_heredoc(command);
		command->tokens_list = command->tokens_list->next;
	}
	return (1);
}
