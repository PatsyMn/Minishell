/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 11:52:12 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static t_command	*new_command(void)
{
	t_command	*cmd;
	t_command	*commands;
	t_command	*cur;
	int			i;
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
}*/
/*static bool	process_redirection(t_token **token, t_command **cur,
		int *expect_command)
{
	if (!token || !(*token))
		return (false);
	if ((*token)->type >= T_REDIR_IN && (*token)->type <= T_HEREDOC)
	{
		handle_redirection(*cur, token);
		*expect_command = 1;
		return (true);
	}
	return (false);
}*/
/*static bool	process_command_word_pipe(t_token **token, t_command **cur,
		int *expect_command, t_pipex *pipex)
{
	if (!token || !(*token))
		return (false);
	if ((*token)->type == T_WORD || (*token)->type == T_COMMAND)
	{
		if (*expect_command)
		{
			(*token)->type = T_COMMAND;
			*expect_command = 0;
		}
		// add_arg(*cur, ft_strdup((*token)->value));
		add_arg(*cur, (*token)->value);
		*token = (*token)->next;
		return (true);
	}
	else if ((*token)->type == T_PIPE)
	{
		pipex->pipe = 1;
		//(*cur)->next = new_command();
		*cur = (*cur)->next;
		*expect_command = 1;
		*token = (*token)->next;
		return (true);
	}
	return (false);
}*/
/*static bool	process_token(t_token **token, t_command **cur,
		int *expect_command, t_pipex *pipex)
{
	if (process_redirection(token, cur, expect_command))
		return (true);
	if (process_command_word_pipe(token, cur, expect_command, pipex))
		return (true);
	return (false);
}*/
/*t_command *parser(t_token *token, t_pipex *pipex)
{
	commands = split_token_list(token);
	cur = commands;
	pipex->pipe = 0;
	while (cur)
	{
		build_args(cur);
		cur = cur->next;
	}
	return (commands);
}*/
// debug
/*void	print_commands(t_command *cmd)
{
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
}*/
static t_command	*new_command(void)
{
	t_command *cmd; 
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->token_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

static t_token	*copy_token(t_token *token)
{
	t_token	*new_tok;

	new_tok = malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->type = token->type;
	new_tok->value = strdup(token->value);
	new_tok->next = NULL;
	return (new_tok);
}

static	int	start_new_command(t_command_split_context *ctx)
{
	t_command	*last;
	
	if (!ctx->current)
	{
		ctx->current= new_command();
		if (!ctx->current)
			return (0);
		if (!ctx->head)
			ctx->head = ctx->current;
		else
		{
			last = ctx->head;
			while (last->next)
				last = last->next;
			last->next = ctx->current;
		}
		ctx->last_token_copy = NULL;
	}
	return (1);
}

static	int	copy_token_list(t_command_split_context *ctx,t_token *token_list)
{	
	ctx->new_token_copy = copy_token(token_list);
	if (!ctx->new_token_copy)
		return (0);
	if (!ctx->current->token_list)
		ctx->current->token_list = ctx->new_token_copy;
	else
		ctx->last_token_copy->next = ctx->new_token_copy;
	ctx->last_token_copy = ctx->new_token_copy;
	return (1);
}

t_command	*split_token_list(t_token *token_list)
{
	t_command_split_context ctx;

	ctx.head = NULL;
	ctx.current = NULL;
	ctx.last_token_copy = NULL;

	while (token_list)
	{
		if (!ctx.current)
    	{
			if (!start_new_command(&ctx))
				return NULL;
		}
		if (token_list->type == T_PIPE)
		{
			ctx.current= NULL;
			token_list = token_list->next;
			continue ;
		}
		copy_token_list(&ctx, token_list);
		token_list = token_list->next;
	}
	return ctx.head;
}

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
