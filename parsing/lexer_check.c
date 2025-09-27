/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:00:05 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/27 16:55:05 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	is_in_quotes(char *str, int *i, int *quotes, int *quote)
{
		if (is_double_quote(&str[*i]))
		{
			if (*quotes == 1)
				*quotes = 0;
			else
				*quotes = 1;
		}
		if (is_single_quote(&str[*i]))
		{
			if (*quote == 1)
				*quote = 0;
			else
				*quote = 1;
		}
}

int	check_special_chars(char *str)
{
	int	i;
	int	quotes;
	int quote;

	i = 0;
	quotes = 0;
	quote = 0;
	while (str[i])
	{
		is_in_quotes(str, &i, &quotes, &quote);
		if ((str[i] == '\\' || str[i] == ';') && quotes == 0
				&& quote == 0)
		{
			printf("bash: Syntax error: unexpected ");
			printf("special character '%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_special_single_char(char *input)
{
	const char	*special_chars;

	special_chars = "!#:";
	if (!input)
		return (0);
	if (input[0] && input[1] == '\0')
	{
		if (ft_strchr(special_chars, input[0]) != NULL)
			return (1);
	}
	return (0);
}
