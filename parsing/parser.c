/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 13:29:52 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	build_args(t_command *cmd)
{
	int		count;
	t_token	*tok;
	char	**args;

	count = 0;
	tok = cmd->token_list;
	while (tok)
	{
		if (tok->type == T_WORD || tok->type == T_COMMAND)
			count++;
		tok = tok->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return ;
	tok = cmd->token_list;
	count = 0;
	while (tok)
	{
		if (tok->type == T_WORD || tok->type == T_COMMAND)
			args[count++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	args[count] = NULL;
	cmd->args = args;
}

t_command	*parser(t_token *tokens_list)
{
	t_command	*commands;
	t_command	*cur;

	commands = split_token_list(tokens_list);
	cur = commands;
	while (cur)
	{
		build_args(cur);
		cur = cur->next;
	}
	return commands;
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
