/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:59:40 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/26 13:32:13 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calculate_processed_length(const char *input, int start, int end)
{
	t_quote_context	context;
	int				i = start;
	int				length = 0;

	init_quote_context(&context);
	while (i < end)
	{
		if (input[i] == '"' && !context.in_single_quote)
			context.in_double_quote = !context.in_double_quote, i++;
		else if (input[i] == '\'' && !context.in_double_quote)
			context.in_single_quote = !context.in_single_quote, i++;
		else if (input[i] == '\\' && i + 1 < end)
			i += 2, length++;
		else
			i++, length++;
	}
	return (length);
}

static void	fill_escaped_string(const char *input, int start, int end, char *word)
{
	t_quote_context	context;
	int				i = start;
	int				j = 0;

	init_quote_context(&context);
	while (i < end)
	{
		if (input[i] == '"' && !context.in_single_quote)
			context.in_double_quote = !context.in_double_quote, i++;
		else if (input[i] == '\'' && !context.in_double_quote)
			context.in_single_quote = !context.in_single_quote, i++;
		else if (input[i] == '\\' && i + 1 < end)
			i++, word[j++] = input[i++];
		else
			word[j++] = input[i++];
	}
	word[j] = '\0';
}

char	*ft_strdup_with_escape(const char *input, int start, int end)
{
	char	*word;
	int		processed_length;

	if (!input || start < 0 || end <= start)
		return (NULL);
	processed_length = calculate_processed_length(input, start, end);
	word = malloc((processed_length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	fill_escaped_string(input, start, end, word);
	return (word);
}

