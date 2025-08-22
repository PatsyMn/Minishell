/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 15:48:51 by pmeimoun         ###   ########.fr       */
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
static void add_arg(t_command *cmd, char *val)
{
	int size;
	char **new_args;
	int i;

	size = 0;
	while (cmd->args && cmd->args[size])
		size++;
	new_args = malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < size)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[size] = val;
	new_args[size + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}
static void	handle_redirection(t_command *cmd, t_token **token)
{
	if (!(*token) || !(*token)->next)
		return ;
	t_token *redir = *token;
	t_token *file = (*token)->next;

	if (redir->type == T_REDIR_IN)
		cmd->infile = ft_strdup(file->value);
	else if (redir->type == T_REDIR_OUT)
	{
		cmd->outfile = ft_strdup(file->value);
		cmd->append = 0;
	}
	else if (redir->type == T_APPEND_OUT)
	{
		cmd->outfile = ft_strdup(file->value);
		cmd->append = 1;
	}
	else if (redir->type == T_HEREDOC)
	{
		cmd->infile = ft_strdup(file->value);
		cmd->heredoc = 1;
	}
	*token = file;
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

//debug 
void	print_commands(t_command *cmd)
{
	int i;

	while (cmd)
	{
		printf("=== Commande ===\n");
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
