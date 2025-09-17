/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:00:05 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/17 14:29:25 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_special_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
		{
			printf("minishell: syntax error near unexpected token `%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_space_or_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_single_char(char *input)
{
	const char *special_chars = "!#:;&|";

	if (!input)
		return 0;
	if (input[0] && input[1] == '\0')
	{
		if (ft_strchr(special_chars, input[0]) != NULL)
			return 1;
	}
	return 0;
}
