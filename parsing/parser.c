/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/01 13:23:49 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
	return (cmd);
}
bool	process_token(t_token **token, t_command **cur, int *expect_command)
{
	if ((*token)->type == T_WORD)
	{
		if (*expect_command)
		{
			(*token)->type = T_COMMAND;
			*expect_command = 0;
		}
		add_arg(*cur, ft_strdup((*token)->value));
		return (false);
	}
	else if ((*token)->type == T_PIPE)
	{
		(*cur)->next = new_command();
		*cur = (*cur)->next;
		*expect_command = 1;
		return (false);
	}
	else if ((*token)->type >= T_REDIR_IN && (*token)->type <= T_HEREDOC)
	{
		handle_redirection(*cur, token);
		return (true);
	}
	return (false);
}

t_command	*parser(t_token *token)
{
	t_command	*head;
	t_command	*cur;
	int			expect_command;
	bool		advanced;

	head = NULL;
	cur = NULL;
	expect_command = 1;
	while (token)
	{
		if (!cur)
		{
			cur = new_command();
			if (!head)
				head = cur;
		}
		advanced = process_token(&token, &cur, &expect_command);
		if (!advanced)
			token = token->next;
	}
	return (head);
}

void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
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
