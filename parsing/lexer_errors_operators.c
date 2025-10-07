/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors_operators.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:27:33 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 15:13:19 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_operator(char *token)
{
	if (!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3)
		|| !ft_strncmp(token, ">", 2) || !ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, "|", 2) || !ft_strncmp(token, "<>", 3))
		return (1);
	return (0);
}

static int	print_syntax_error(char *token)
{
	if (token)
	{
		g_status = 2;
		printf("minishell: syntax error near unexpected token `%s'\n", token);
	}
	else
	{
		g_status = 2;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (1);
}

static int	check_operator_at_end(char *token)
{
	(void)token;
	g_status = 2;
	printf("minishell: syntax error near unexpected token `newline'\n");
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
				if (ft_strncmp(split_input[i], "<", 2) == 0 && ft_strncmp(split_input[i + 1], ">", 2) == 0)
					return (print_syntax_error(NULL));
				return (print_syntax_error(split_input[i + 1]));
			}
		}
		i++;
	}
	return (0);
}

