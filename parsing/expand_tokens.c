/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:52:49 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 12:06:00 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_variable_token(t_token *token, t_env *env_copy)
{
	t_expansion	exp;

	exp = prepare_expansion(token->value, env_copy);
	if (!exp.result)
		exp.expanded = build_expansion(&exp);
	else
		exp.expanded = exp.result;
	if (exp.expanded)
	{
		free(token->value);
		token->value = exp.expanded;
		exp.expanded = NULL;
		exp.result = NULL;
	}
	free_exp(&exp);
}

static void	process_double_quoted_token(t_token *token)
{
	char	*tmp;

	tmp = token->value;
	token->value = strip_outer_double_quotes(token->value);
	if (tmp != token->value)
		free(tmp);
}

int	expand_tokens(t_token *tokens, t_env *env_copy)
{
	while (tokens)
	{
		if (tokens->type == T_DOLLAR_VAR && tokens->value[0] == '$'
			&& tokens->value[1] != '\0' && tokens->value[1] != '?')
			expand_variable_token(tokens, env_copy);
		else if (tokens->type == T_DOUBLE_QUOTE)
			process_double_quoted_token(tokens);
		else if (tokens->type == T_REDIR_OUT && !tokens->next)
		{
			g_status = 2;
			printf("WhatTheShell: syntax error near ");
			printf("unexpected token `newline'\n");
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
