/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:59:40 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/02 11:14:22 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calculate_processed_length(const char *input, int start, int end)
{
	t_quote_context	context;
	int				i;
	int				length;

	i = start;
	length = 0;
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
static void	handle_quote_char(const char *input, int *i,
								t_quote_context *context)
{
	if (input[*i] == '"' && !context->in_single_quote)
	{
		context->in_double_quote = !context->in_double_quote;
		(*i)++;
	}
	else if (input[*i] == '\'' && !context->in_double_quote)
	{
		context->in_single_quote = !context->in_single_quote;
		(*i)++;
	}
}

static int	handle_escape_or_char(const char *input, int *i, int end,
								char *word, int *j)
{
	if (input[*i] == '\\' && *i + 1 < end)
	{
		(*i)++;
		word[(*j)++] = input[(*i)++];
		return (1);
	}
	word[(*j)++] = input[(*i)++];
	return (0);
}

static void	fill_escaped_string(const char *input, int start, int end, char *word)
{
	t_quote_context	context;
	int				i;
	int				j;

	i = start;
	j = 0;
	init_quote_context(&context);
	while (i < end)
	{
		handle_quote_char(input, &i, &context);
		if (i >= end)
			break ;
		if (handle_escape_or_char(input, &i, end, word, &j) == 0)
			continue ;
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

