/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:40:18 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/19 16:00:27 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

int	check_invalid_tokens(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == T_INVALID_OPERATOR)
		{
			printf("bash: syntax error near");
			printf("unexpected token `%s'\n", tmp->value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	mark_commands(t_token *tokens)
{
	int	expect_command;

	expect_command = 1;
	while (tokens)
	{
		if (tokens->type == T_REDIR_IN || tokens->type == T_REDIR_OUT
			|| tokens->type == T_APPEND_OUT || tokens->type == T_HEREDOC)
		{
			if (tokens->next)
				tokens = tokens->next;
		}
		else if (tokens->type == T_WORD && expect_command)
		{
			tokens->type = T_COMMAND;
			expect_command = 0;
		}
		else if (tokens->type == T_PIPE)
		{
			expect_command = 1;
		}
		tokens = tokens->next;
	}
}
