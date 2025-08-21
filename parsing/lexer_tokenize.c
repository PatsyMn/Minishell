/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/21 15:44:29 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token_type	get_token_type(char c)
{
	if (c == '\'')
		return (T_SINGLE_QUOTE);
	if (c == '"')
		return (T_DOUBLE_QUOTE);
	if (c == '|')
		return (T_PIPE);
	return (T_WORD);
}

static t_token_type get_token_type_from_str_with_char(char *str)
{
	if (!str || !str[0])
		return (T_WORD);
	if (str[0] == '|' && str[1] == '\0')
		return (T_PIPE);
	t_token_type type = get_token_type(str[0]);
	if (type == T_SINGLE_QUOTE && str[ft_strlen(str) - 1] == '\'')
		return (T_SINGLE_QUOTE);
	if (type == T_DOUBLE_QUOTE && str[ft_strlen(str) - 1] == '"')
		return (T_DOUBLE_QUOTE);
	return (T_WORD);
}

t_token *tokenizer(char **split_input)
{
	t_token *token_list = NULL;
	t_token *new_token = NULL;
	int i = 0;
	while (split_input[i])
	{
		t_token_type type = get_token_type_from_str_with_char(split_input[i]);
		new_token = create_token(type, ft_strdup(split_input[i]));
		add_token_to_list(&token_list, new_token);
		i++;
	}
	return (token_list);
}

