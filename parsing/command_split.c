/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:29:30 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/15 13:11:50 by pmeimoun         ###   ########.fr       */
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
	new_tok->value = ft_strdup(token->value);
	new_tok->next = NULL;
	return (new_tok);
}

static int	start_new_command(t_command_split_context *ctx)
{
	t_command	*last;

	if (!ctx->current)
	{
		ctx->current = new_command();
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

static int	copy_token_list(t_command_split_context *ctx, t_token *token_list)
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
	t_command_split_context	ctx;

	ctx.head = NULL;
	ctx.current = NULL;
	ctx.last_token_copy = NULL;
	while (token_list)
	{
		if (!ctx.current)
		{
			if (!start_new_command(&ctx))
				return (NULL);
		}
		if (token_list->type == T_PIPE)
		{
			ctx.current = NULL;
			token_list = token_list->next;
			continue ;
		}
		copy_token_list(&ctx, token_list);
		token_list = token_list->next;
	}
	return (ctx.head);
}
