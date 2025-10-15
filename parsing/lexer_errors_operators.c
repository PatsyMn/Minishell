/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors_operators.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:27:33 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/15 11:57:04 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_operator(char *token)
{
	if (!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3)
		|| !ft_strncmp(token, ">", 2) || !ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, "<>", 3) || !ft_strncmp(token, "|", 2))
		return (1);
	return (0);
}

static int	print_syntax_error(char *token)
{
	if (token)
	{
		g_status = 2;
		printf("WhatTheShell: syntax error near ");
		printf("unexpected token `%s'\n", token);
	}
	else
	{
		g_status = 2;
		printf("WhatTheShell: syntax error near ");
		printf("unexpected token `newline'\n");
	}
	return (1);
}

int	check_syntax_operators(char **split_input)
{
	int	i;

	i = 0;
	while (split_input[i])
	{
		if (!ft_strncmp(split_input[i], "||", 3))
			return (print_syntax_error("||"));
		if (is_operator(split_input[i]))
		{
			if (split_input[i + 1])
			{
				if (is_operator(split_input[i + 1])
					&& !ft_strncmp(split_input[i], split_input[i + 1],
						ft_strlen(split_input[i])))
					return (print_syntax_error(split_input[i]));
				if (is_operator(split_input[i + 1]) && !split_input[i + 2])
					return (print_syntax_error(NULL));
			}
		}
		if (is_operator(split_input[i]) && !i && !split_input[i + 1])
			return (print_syntax_error(NULL));
		i++;
	}
	return (0);
}
