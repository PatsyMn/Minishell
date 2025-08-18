/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:38:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/18 15:16:31 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote_context(t_quote_context *context, char c)
{
	if (c == '\'' && !context->in_double_quote)
		context->in_single_quote = !context->in_single_quote;
	else if (c == '"' && !context->in_single_quote)
		context->in_double_quote = !context->in_double_quote;
}

int	disable_metachar_in_single_quotes(t_quote_context *context)
{
	return (context->in_single_quote);
}

int	disable_metachar_in_double_quotes(t_quote_context *context, char c)
{
	if (!context->in_double_quote)
		return (0);
	if (c == '$')
		return (0);
	return (1);
}

void	init_quote_context(t_quote_context *context)
{
	context->in_single_quote = 0;
	context->in_double_quote = 0;
}

int	is_pipe(char c, int in_single_quote, int in_double_quote)
{
	return (c == '|' && !in_single_quote && !in_double_quote);
}

