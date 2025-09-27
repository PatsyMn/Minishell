/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:57:48 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/27 16:00:25 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_whitespace(t_split_state *state)
{
	if (state->start == -1 && (state->input[state->i] == ' '
			|| state->input[state->i] == 9))
	{
		state->i++;
		return (1);
	}
	if (state->start == -1 && (state->input[state->i] != ' '
			&& state->input[state->i] != 9))
		state->start = state->i;
	return (0);
}

static int	handle_operators(t_split_state *state)
{
	char	c;

	if (state->context->in_single_quote || state->context->in_double_quote)
		return (0);
	c = state->input[state->i];
	if (c == '>' || c == '<')
	{
		handle_redirect(state);
		return (1);
	}
	if (c == '|')
	{
		handle_pipe(state);
		return (1);
	}
	return (0);
}

char	**split_loop(t_split_state *state)
{
	while (state->input[state->i])
	{
		printf("caca %c \n", state->input[state->i]);
		if (skip_whitespace(state))
			continue ;
		update_quote_context(state->context, state->input[state->i]);
		if (handle_operators(state))
			continue ;
		handle_space_or_end(state);
	}
	return (state->result);
}
