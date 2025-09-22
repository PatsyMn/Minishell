/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_word_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:24:19 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/19 13:26:53 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_and_add_word(t_split_state *state)
{
	int		end;
	char	*word;

	if (state->input[state->i] == ' ' || state->input[state->i] == 9)
		end = state->i;
	else
		end = state->i + 1;
	word = ft_substr(state->input, state->start, end - state->start);
	if (!word)
	{
		free_split(state->result);
		return (NULL);
	}
	state->result = add_word_to_tab(state->result, word);
	if (!state->result)
		return (NULL);
	return (state->result);
}

char	**add_word_to_tab(char **tab, char *word)
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

int	handle_split_word(t_split_state *state)
{
	state->result = split_and_add_word(state);
	if (!state->result)
		return (0);
	return (1);
}
