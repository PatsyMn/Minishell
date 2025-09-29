/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/22 16:03:57 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->limiter = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
	return (cmd);
}

static bool	process_redirection(t_token **token, t_command **cur, int *expect_command)
{
	if (!token || !(*token))
		return false;

	if ((*token)->type >= T_REDIR_IN && (*token)->type <= T_HEREDOC)
	{
		handle_redirection(*cur, token);
		*expect_command = 1;
		return true;
	}
	return false;
}

static bool	process_command_word_pipe(t_token **token, t_command **cur, int *expect_command)
{
	if (!token || !(*token))
		return false;

	if ((*token)->type == T_WORD || (*token)->type == T_COMMAND)
	{
		if (*expect_command)
		{
			(*token)->type = T_COMMAND;
			*expect_command = 0;
		}
		add_arg(*cur, ft_strdup((*token)->value));
		*token = (*token)->next;
		return true;
	}
	else if ((*token)->type == T_PIPE)
	{
		(*cur)->next = new_command();
		*cur = (*cur)->next;
		*expect_command = 1;
		*token = (*token)->next;
		return true;
	}
	return false;
}
static bool	process_token(t_token **token, t_command **cur, int *expect_command)
{
	if (process_redirection(token, cur, expect_command))
		return true;
	if (process_command_word_pipe(token, cur, expect_command))
		return true;
	return false;
}

t_command *parser(t_token *token)
{
	t_command *head = NULL;
	t_command *cur = NULL;
	int expect_command = 1;

	while (token)
	{
		if (!cur)
		{
			cur = new_command();
			if (!head)
				head = cur;
		}
		if (!process_token(&token, &cur, &expect_command))
			token = token->next;
	}
	return (head);
}

// debug
void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("=== Command ===\n");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("Arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		if (cmd->infile)
			printf("Infile: %s (heredoc: %d)\n", cmd->infile, cmd->heredoc);
		if (cmd->outfile)
			printf("Outfile: %s (append: %d)\n", cmd->outfile, cmd->append);
		cmd = cmd->next;
	}
}
