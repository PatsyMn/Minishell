/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:39:15 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/28 14:34:23 by pmeimoun         ###   ########.fr       */
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

static int	check_unclosed_single_quote(char *str)
{
	int	i;
	int	in_single_quote;

	i = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		i++;
	}
	if (in_single_quote)
	{
		printf("Syntax error: unclosed single quote\n");
		return (1);
	}
	return (0);
}

static int	check_unclosed_double_quote(char *str)
{
	int	i;
	int	in_double_quote;

	i = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_double_quote)
	{
		printf("Syntax error: unclosed double quote\n");
		return (1);
	}
	return (0);
}

int	check_unclosed_quotes(char *str)
{
	if (check_unclosed_single_quote(str))
		return (1);
	if (check_unclosed_double_quote(str))
		return (1);
	return (0);
}

int	check_special_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
		{
			printf("Syntax error: unexpected special character '%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
