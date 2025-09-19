/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_loop_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:10:50 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/19 15:03:44 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirect(t_split_state *state)
{
	if (state->start != state->i)
	{
		if (!handle_split_word(state))
			return;
		state->start = state->i;
	}
	if (state->input[state->i + 1] == state->input[state->i])
		state->i++;
	if (!handle_split_word(state))
		return;
	state->start = -1;
	state->i++;
}

void handle_pipe(t_split_state *state)
{
	if (state->start != state->i)
	{
		if (!handle_split_word(state))
			return;
		state->start = state->i;
	}
	if (state->input[state->i + 1] == '|')
		state->i++;
	if (!handle_split_word(state))
		return;
	state->start = -1;
	state->i++;
}

void	handle_space_or_end(t_split_state *state)
{
	int	c;

	c = state->input[state->i];
	if (((c == ' ' || c == 9) && !state->context->in_single_quote
			&& !state->context->in_double_quote)
		|| state->input[state->i + 1] == '\0')
	{
		if (state->start >= 0)
		{
			if (!handle_split_word(state))
				return;
			state->start = -1;
		}
	}
	state->i++;
}

