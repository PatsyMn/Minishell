/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:55:11 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 13:00:38 by pmeimoun         ###   ########.fr       */
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
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' '
		&& operator_len(&str[*i]) == 0)
	{
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	sub = ft_substr(str, start, *i - start);
	return (sub);
}

char	*append_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*process_segment(char *str, int *i, t_env *env_copy)
{
	char	*tmp;
	char	*expanded;

	if (str[*i] == '\'')
	{
		tmp = extract_quoted_substring(str, i);
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
