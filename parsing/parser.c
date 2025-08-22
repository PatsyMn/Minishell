/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 18:47:21 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*new_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
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

t_command	*parser(t_token *token)
{
	t_command	*head = NULL;
	t_command	*cur = NULL;

	while (token)
	{
		if (!cur)
		{
			cur = new_command();
			if (!head)
				head = cur;
		}
		if (token->type == T_WORD)
			add_arg(cur, ft_strdup(token->value));
		else if (token->type == T_PIPE)
		{
			cur->next = new_command();
			cur = cur->next;
		}
		else if (token->type >= T_REDIR_IN && token->type <= T_HEREDOC)
			handle_redirection(cur, &token);
		token = token->next;
	}
	return (head);
}

void	free_commands(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
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
}
//debug 
void	print_commands(t_command *cmd)
{
	int i;

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
