/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:46:14 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/10 14:43:17 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_quoted_word(char *str, int *i)
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

static char	*append_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new_str);
}

static int	handle_unquoted_word(char *str, int *i, char **buffer)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' &&
			str[*i] != ' ' && operator_length(&str[*i]) == 0)
	{
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	tmp = ft_substr(str, start, *i - start);
	if (!tmp)
		return (0);
	*buffer = append_and_free(*buffer, tmp);
	return (1);
}

static int	build_word_buffer(char *str, int *i, char **buffer)
{
	char	*tmp;

	while (str[*i] && str[*i] != ' ' && operator_length(&str[*i]) == 0)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			tmp = handle_quoted_word(str, i);
			if (!tmp)
				return (0);
			*buffer = append_and_free(*buffer, tmp);
		}
		else
		{
			if (!handle_unquoted_word(str, i, buffer))
				return (0);
		}
	}
	return (1);
}

int	handle_word(char *str, int *i, t_token **token_list)
{
	char	*buffer;
	int		ret;

	buffer = ft_strdup("");
	if (!buffer)
		return (0);
	ret = build_word_buffer(str, i, &buffer);
	if (ret)
	{
		add_token_to_list(token_list, create_token(T_WORD, buffer));
		ret = 1;
	}
	return (ret);
}



