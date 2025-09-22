/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:32:31 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/19 15:35:21 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_syntax_error_first_pipe(char **split_input)
{
	if (!split_input || !split_input[0])
		return (0);
	if (ft_strncmp(split_input[0], "|", 2) == 0)
	{
		printf("bash: syntax error near unexpected token `|'\n");
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
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	has_syntax_error_ampersand(char **split_input)
{
	int	i;

	i = 0;
	if (!split_input)
		return (0);
	while (split_input[i])
		i++;
	if (i > 0 && ft_strncmp(split_input[i - 1], "&&", 2) == 0)
	{
		printf("bash: syntax error near unexpected token `&&'\n");
		return (1);
	}
	return (0);
}
