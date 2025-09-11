/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:52:49 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/11 13:52:59 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_variable_token(t_token *token, char **env_copy)
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

void	expand_tokens(t_token *tokens, char **env_copy)
{
	while (tokens)
	{
		if (tokens->type == T_DOLLAR_VAR)
			expand_variable_token(tokens, env_copy);
		else if (tokens->type == T_DOUBLE_QUOTE)
			process_double_quoted_token(tokens);
		tokens = tokens->next;
	}
}
