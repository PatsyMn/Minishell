/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:59:40 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/02 13:27:01 by pmeimoun         ###   ########.fr       */
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
		update_quote_context(&context, input[i]);
		if (input[i] == '\\' && i + 1 < end)
		{
			i += 2;
			length++;
		}
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

static void	handle_quote_char(t_input *input, t_quote_context *context)
{
	if (input->str[input->index] == '"' && !context->in_single_quote)
	{
		context->in_double_quote = !context->in_double_quote;
		input->index++;
		return ;
	}
	if (input->str[input->index] == '\'' && !context->in_double_quote)
	{
		context->in_single_quote = !context->in_single_quote;
		input->index++;
	}
}

static int	handle_escape_or_char(t_input *input, t_output *output)
{
	if (input->str[input->index] == '\\' && input->index + 1 < input->end)
	{
		input->index++;
		output->str[output->index++] = input->str[input->index++];
		return (1);
	}
	output->str[output->index++] = input->str[input->index++];
	return (0);
}

static void	fill_escaped_string(const char *input_str, int start,
												int end, char *word)
{
	t_quote_context	context;
	t_input			input;
	t_output		output;

	init_quote_context(&context);
	input.str = input_str;
	input.index = start;
	input.end = end;
	output.str = word;
	output.index = 0;
	while (input.index < input.end)
	{
		handle_quote_char(&input, &context);
		if (input.index < input.end)
			handle_escape_or_char(&input, &output);
	}
	output.str[output.index] = '\0';
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
