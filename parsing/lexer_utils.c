/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:50:54 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/28 16:00:16 by pmeimoun         ###   ########.fr       */
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

static char	**add_word_to_tab(char **tab, char *word)
{
	int		size;
	char	**new_tab;
	int		i;

	size = 0;
	while (tab && tab[size])
		size++;
	new_tab = malloc(sizeof(char *) * (size + 2));
	if (!new_tab)
	{
		free(word);
		free_split(tab);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[size] = word;
	new_tab[size + 1] = NULL;
	free(tab);
	return (new_tab);
}

static char	**split_and_add_word(t_split_state *state)
{
	int		end;
	char	*word;

	if (state->input[state->i] == ' ')
		end = state->i;
	else
		end = state->i + 1;
	word = ft_substr(state->input, state->start, end - state->start);
	if (!word)
		return (free_split(state->result), NULL);
	state->result = add_word_to_tab(state->result, word);
	if (!state->result)
		return (NULL);
	return (state->result);
}

static char	**split_loop(t_split_state *state)
{
	while (state->input[state->i])
	{
		update_quote_context(state->context, state->input[state->i]);
		if (state->input[state->i] != ' ' && state->start < 0)
			state->start = state->i;
		if (((state->input[state->i] == ' ' && !state->context->in_single_quote
					&& !state->context->in_double_quote)
				|| state->input[state->i + 1] == '\0') && state->start >= 0)
		{
			state->result = split_and_add_word(state);
			if (!state->result)
				return (NULL);
			state->start = -1;
		}
		state->i++;
	}
	return (state->result);
}
char	**split_input_respecting_quotes(char *input)
{
	t_quote_context	context;
	t_split_state	state;

	init_quote_context(&context);
	state.result = NULL;
	state.input = input;
	state.context = &context;
	state.start = -1;
	state.i = 0;
	if (!split_loop(&state))
		return (NULL);
	return (state.result);
}
int	has_syntax_error_first_pipe(char **split_input)
{
	if (!split_input || !split_input[0])
		return (0);
	if (ft_strncmp(split_input[0], "|", 2) == 0)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (1);
	}
	return (0);
}
int	has_syntax_error_last_pipe(char **split_input)
{
	int	i;

	i = 0;
	if (!split_input)
		return (0);
	while (split_input[i])
		i++;
	if (i > 0 && ft_strncmp(split_input[i - 1], "|", 2) == 0)
	{
		printf("syntax error near unexpected token '|'\n");
		return (1);
	}
	return (0);
}

static int	is_operator(char *token)
{
	if (!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3)
		|| !ft_strncmp(token, ">", 2) || !ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, "|", 2))
		return (1);
	return (0);
}

static int	check_operator_at_end(char *token)
{
	(void)token;
	printf("syntax error near unexpected token\n");
	return (1);
}

int	check_syntax_operators(char **split_input)
{
	int	i;

	i = 0;
	while (split_input[i])
	{
		if (is_operator(split_input[i]))
		{
			if (!split_input[i + 1])
				return (check_operator_at_end(split_input[i]));
			if (is_operator(split_input[i + 1]))
			{
				printf("syntax error near unexpected token '%s'\n",
					split_input[i + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
