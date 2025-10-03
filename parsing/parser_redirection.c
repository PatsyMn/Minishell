/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:29:50 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/03 13:38:30 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_redirection_in(t_command *cmd, t_token **token)
{
	t_token	*redir;
	t_token	*file;

	if (!(*token) || !(*token)->next)
		return ;
	redir = *token;
	file = (*token)->next;
	if (redir->type == T_REDIR_IN)
	{
		cmd->infile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->heredoc = 0;
	}
	else if (redir->type == T_HEREDOC)
	{
		cmd->infile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->heredoc = 1;
	}
	*token = file->next;
}

static void	handle_redirection_out(t_command *cmd, t_token **token)
{
	t_token	*redir;
	t_token	*file;

	if (!(*token) || !(*token)->next)
		return ;
	redir = *token;
	file = (*token)->next;
	if (redir->type == T_REDIR_OUT)
	{
		cmd->outfile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->append = 0;
	}
	else if (redir->type == T_APPEND_OUT)
	{
		cmd->outfile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->append = 1;
	}
	*token = file->next;
}

void	handle_redirection(t_command *cmd, t_token **token)
{
	if (!token || !(*token))
		return ;
	if ((*token)->type == T_REDIR_IN || (*token)->type == T_HEREDOC)
		handle_redirection_in(cmd, token);
	else if ((*token)->type == T_REDIR_OUT || (*token)->type == T_APPEND_OUT)
		handle_redirection_out(cmd, token);
}
