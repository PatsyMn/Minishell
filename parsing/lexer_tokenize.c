/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/26 16:47:00 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	operator_length(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	if (*str == '>' || *str == '<' || *str == '|')
		return (1);
	return (0);
}
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

static int	tokenize_str(char *str, t_token **token_list)
{
	int		i = 0;
	int		op_len;
	char	*sub;

	while (str[i])
	{
		op_len = operator_length(&str[i]);
		if (op_len > 0)
		{
			sub = ft_substr(str, i, op_len);
			if (!sub)
				return (0);
			add_token_to_list(token_list, create_token(get_token_type_from_str(sub), sub));
			i += op_len;
		}
		else
		{
			int	start = i;
			while (str[i] && operator_length(&str[i]) == 0)
				i++;
			sub = ft_substr(str, start, i - start);
			if (!sub)
				return (0);
			add_token_to_list(token_list, create_token(T_WORD, sub));
		}
	}
	return (1);
}

t_token	*tokenizer(char **split_input)
{
	t_token	*token_list = NULL;
	int		i = 0;

	while (split_input[i])
	{
		if (!tokenize_str(split_input[i], &token_list))
		{
			free_tokens(token_list);
			return (NULL);
		}
		i++;
	}
	mark_commands(token_list);
	return (token_list);
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

void	mark_commands(t_token *tokens)
{
	int	expect_command = 1;

	while (tokens)
	{
		if (tokens->type == T_WORD && expect_command)
		{
			tokens->type = T_COMMAND;
			expect_command = 0;
		}
		else if (tokens->type == T_PIPE)
		{
			expect_command = 1;
		}
		tokens = tokens->next;
	}
}
//debug
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-12s | Value: %s\n",
			(tokens->type == T_COMMAND) ? "COMMAND" :
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
