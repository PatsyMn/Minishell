/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/14 17:54:10 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	get_token_type_from_str(char *str)
{
	if (!str)
		return (T_WORD);
	if (is_single_quote(str))
		return (T_SINGLE_QUOTE);
	if (is_double_quote(str))
		return (T_DOUBLE_QUOTE);
	if (is_invalid_operator(str))
		return (T_INVALID_OPERATOR);
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

static int	tokenize_str(char *str, t_token **token_list, t_env *env_copy)
{
	int	i;
	int	ret;

	i = 0;
	while (str[i])
	{
		ret = handle_operator(str, &i, token_list);
		if (ret == -1)
			return (0);
		if (ret == 0 && !handle_word(str, &i, token_list, env_copy))
			return (0);
	}
	return (1);
}

t_token	*tokenizer(char **split_input, t_env *env_copy)
{
	t_token	*token_list;
	int		i;

	token_list = NULL;
	i = 0;
	while (split_input[i])
	{
		if (!tokenize_str(split_input[i], &token_list, env_copy))
		{
			free_tokens(token_list);
			return (NULL);
		}
		i++;
	}
	detect_command_tokens(token_list);
	if (check_invalid_tokens(token_list))
	{
		free_tokens(token_list);
		return (NULL);
	}
	return (token_list);
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
