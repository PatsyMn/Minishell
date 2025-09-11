/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:46:14 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/10 16:51:20 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_quoted_substring(char *str, int *i)
{
	char	quote;
	int		start;
	char	*sub;

	quote = str[*i];
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	if (str[*i] != quote)
		return (NULL);
	(*i)++;
	sub = ft_substr(str, start + 1, *i - start - 2);
	return (sub);
}

static char	*extract_unquoted_segment(char *str, int *i)
{
	int		start;
	char	*sub;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"'
		&& str[*i] != ' ' && operator_length(&str[*i]) == 0)
	{
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	sub = ft_substr(str, start, *i - start);
	return (sub);
}

static char	*append_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new_str);
}

static char	*process_segment(char *str, int *i, char **env_copy)
{
	char	*tmp;
	char	*expanded;

	if (str[*i] == '\'')
	{
		tmp = extract_quoted_substring(str, i);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	if (str[*i] == '"')
	{
		tmp = extract_quoted_substring(str, i);
		if (!tmp)
			return (NULL);
		expanded = expand_variables(tmp, env_copy);
		free(tmp);
		return (expanded);
	}
	tmp = extract_unquoted_segment(str, i);
	if (!tmp)
		return (NULL);
	expanded = expand_variables(tmp, env_copy);
	free(tmp);
	return (expanded);
}

int	handle_word(char *str, int *i, t_token **token_list, char **env_copy)
{
	char	*buffer;
	char	*segment;
	int		continue_loop;

	buffer = ft_strdup("");
	if (!buffer)
		return (0);
	continue_loop = 1;
	while (str[*i] && str[*i] != ' ' && operator_length(&str[*i]) == 0 && continue_loop)
	{
		segment = process_segment(str, i, env_copy);
		if (!segment)
			continue_loop = 0;
		else
			buffer = append_and_free(buffer, segment);
	}
	if (!*buffer)
	{
		free(buffer);
		return (0);
	}
	add_token_to_list(token_list, create_token(T_WORD, buffer));
	return (1);
}




