/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/25 16:01:55 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token_type	get_token_type_from_str(char *str)
{
	if (!str)
		return (T_WORD);
	if (!ft_strncmp(str, ">>", 3))
		return (T_APPEND_OUT);
	if (!ft_strncmp(str, "<<", 3))
		return (T_HEREDOC);
	if (!ft_strncmp(str, "|", 2))
		return (T_PIPE);
	if (!ft_strncmp(str, "<", 2))
		return (T_REDIR_IN);
	if (!ft_strncmp(str, ">", 2))
		return (T_REDIR_OUT);
	if (str[0] == '$' && ft_strlen(str) > 1)
		return (T_DOLLAR_VAR);
	return (T_WORD);
}

int	count_tokens(t_token *tokens)
{
	int	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}
char	**tokens_to_tab(t_token *tokens)
{
	int		len;
	char	**tab;
	int		i;

	len = count_tokens(tokens);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (tokens)
	{
		tab[i] = ft_strdup(tokens->value);
		if (!tab[i])
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			return (NULL);
		}
		i++;
		tokens = tokens->next;
	}
	tab[i] = NULL;
	return (tab);
}

t_token *tokenizer(char **split_input)
{
	t_token *token_list = NULL;
	t_token *new_token = NULL;
	int i;
	char *dup;

	i = 0;
	while (split_input[i])
	{
		dup = ft_strdup(split_input[i]);
		if (!dup)
		{
			free_tokens(token_list);
			return (NULL);
		}
		new_token = create_token(get_token_type_from_str(split_input[i]), dup);
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
			(tokens->type == T_DOLLAR_VAR) ? "DOLLAR_VAR" :
			(tokens->type == T_WORD) ? "WORD" :
			(tokens->type == T_PIPE) ? "PIPE" :
			(tokens->type == T_REDIR_IN) ? "REDIR_IN" :
			(tokens->type == T_REDIR_OUT) ? "REDIR_OUT" :
			(tokens->type == T_APPEND_OUT) ? "APPEND_OUT" :
			(tokens->type == T_HEREDOC) ? "HEREDOC" :
			"UNKNOWN",
			tokens->value);
		tokens = tokens->next;
	}
}

