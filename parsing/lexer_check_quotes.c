/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:39:15 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 12:17:58 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_double_quote(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	return (str[0] == '"' && str[len - 1] == '"');
}

int	is_single_quote(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	return (str[0] == '\'' && str[len - 1] == '\'');
}

static t_quote_state	parse_quotes(char *str)
{
	int				i;
	t_quote_state	state;

	i = 0;
	state = NO_QUOTE;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			continue;
		}
		if (str[i] == '\'' && state == NO_QUOTE)
			state = IN_SINGLE;
		else if (str[i] == '\'' && state == IN_SINGLE)
			state = NO_QUOTE;
		else if (str[i] == '"' && state == NO_QUOTE)
			state = IN_DOUBLE;
		else if (str[i] == '"' && state == IN_DOUBLE)
			state = NO_QUOTE;
		i++;
	}
	return (state);
}

int	check_unclosed_quotes(char *str)
{
	t_quote_state	state;

	if (!str)
		return (0);
	state = parse_quotes(str);
	if (state == IN_SINGLE)
	{
		printf("WhatTheShell: syntax error: unclosed single quote\n");
		return (1);
	}
	if (state == IN_DOUBLE)
	{
		printf("WhatTheShell: syntax error: unclosed double quote\n");
		return (1);
	}
	return (0);
}

