/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/21 18:07:47 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	tok_to_args(t_command *cmd, t_token *token, int count, char **args)
{
	while (token)
	{
		if (token->type == T_WORD || token->type == T_COMMAND
			|| token->type == T_SINGLE_QUOTE || token->type == T_DOUBLE_QUOTE
			|| token->type == T_DOLLAR_VAR)
			args[count++] = ft_strdup(token->value);
		token = token->next;
	}
	args[count] = NULL;
	cmd->args = args;
}

void	build_args(t_command *cmd)
{
	int		count;
	t_token	*token;
	char	**args;

	count = 0;
	token = cmd->token_list;
	while (token)
	{
		if (token->type == T_WORD || token->type == T_COMMAND
			|| token->type == T_SINGLE_QUOTE || token->type == T_DOUBLE_QUOTE
			|| token->type == T_DOLLAR_VAR)
			count++;
		token = token->next;
	}
	if (!count)
	{
		cmd->args = NULL;
		return ;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return ;
	token = cmd->token_list;
	count = 0;
	tok_to_args(cmd, token, count, args);
}

t_command	*parser(t_token *tokens_list)
{
	t_command	*commands;
	t_command	*current_cmd;

	commands = split_token_list(tokens_list);
	current_cmd = commands;
	while (current_cmd)
	{
		build_args(current_cmd);
		current_cmd = current_cmd->next;
	}
	return (commands);
}
