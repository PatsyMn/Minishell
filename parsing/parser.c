/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/14 15:41:18 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	build_args(t_command *cmd)
{
	int		count;
	t_token	*token;
	char	**args;

	count = 0;
	token = cmd->token_list;
	while (token)
	{
		if (token->type == T_WORD || token->type == T_COMMAND)
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
	while (token)
	{
		if (token->type == T_WORD || token->type == T_COMMAND)
			args[count++] = ft_strdup(token->value);
		token = token->next;
	}
	args[count] = NULL;
	cmd->args = args;
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

// Debug print
void	print_commands(t_command *cmd)
{
	int		i;
	t_token	*tok;

	while (cmd)
	{
		printf("=== Command ===\n");
		// Affichage des arguments
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("Arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		else
			printf("No args\n");
		// Optionnel : affichage des tokens associés
		tok = cmd->token_list;
		if (tok)
		{
			printf("--- Tokens ---\n");
			while (tok)
			{
				printf("Token: %-10s | Type: %d\n", tok->value, tok->type);
				tok = tok->next;
			}
		}
		printf("\n");
		cmd = cmd->next;
	}
}
