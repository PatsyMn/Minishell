/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:32:31 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/10 17:24:20 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
