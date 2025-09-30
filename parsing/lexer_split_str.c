/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:50:54 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/30 15:34:05 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split_input)
{
	int	i;

	if (!split_input)
		return ;
	i = 0;
	while (split_input[i])
	{
		free(split_input[i]);
		i++;
	}
	free(split_input);
}

char	**split_input_respecting_quotes(char *input)
{
	t_quote_context	context;
	t_split_state	state;

	if (is_special_single_char(input))
		return (NULL);
	init_quote_context(&context);
	state.result = NULL;
	state.input = input;
	state.context = &context;
	state.start = -1;
	state.i = 0;
	state.start = -1;
	if (!split_loop(&state))
		return (NULL);
	return (state.result);
}
