/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 15:03:47 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token_type	get_token_type_from_str(char *str)
{
	if (!str)
		return (T_WORD);
	if (!ft_strncmp(str, "|", 2))
		return (T_PIPE);
	if (!ft_strncmp(str, "<", 2))
		return (T_REDIR_IN);
	if (!ft_strncmp(str, ">", 2))
		return (T_REDIR_OUT);
	if (!ft_strncmp(str, ">>", 3))
		return (T_APPEND_OUT);
	if (!ft_strncmp(str, "<<", 3))
		return (T_HEREDOC);
	return (T_WORD);
}

t_token *tokenizer(char **split_input)
{
	t_token *token_list = NULL;
	t_token *new_token = NULL;
	int i = 0;
	while (split_input[i])
	{
		t_token_type type = get_token_type_from_str(split_input[i]);
		new_token = create_token(type, ft_strdup(split_input[i]));
		add_token_to_list(&token_list, new_token);
		i++;
	}
	return (token_list);
}
//debug
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-12s | Value: %s\n",
			(tokens->type == T_WORD) ? "WORD" :
			(tokens->type == T_PIPE) ? "PIPE" :
			(tokens->type == T_REDIR_IN) ? "REDIR_IN" :
			(tokens->type == T_REDIR_OUT) ? "REDIR_OUT" :
			(tokens->type == T_APPEND_OUT) ? "APPEND_OUT" :
			(tokens->type == T_HEREDOC) ? "HEREDOC" : "UNKNOWN",
			tokens->value);
		tokens = tokens->next;
	}
}
