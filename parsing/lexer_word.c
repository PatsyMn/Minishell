/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:46:14 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/02 11:04:34 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_word_token(char *str, int start, int *i, t_token **token_list)
{
	char	*sub;

	sub = ft_substr(str, start, *i - start);
	if (!sub)
		return (0);
	add_token_to_list(token_list, create_token(get_token_type_from_str(sub),
			sub));
	return (1);
}

int	handle_word(char *str, int *i, t_token **token_list)
{
	int	start;

	start = *i;
	while (str[*i])
	{
		if (operator_length(&str[*i]) > 0)
		{
			return (add_word_token(str, start, i, token_list));
		}
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	return (add_word_token(str, start, i, token_list));
}
