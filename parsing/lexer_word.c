/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:46:14 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 12:55:50 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*build_word_buffer(char *str, int *i, t_env *env_copy)
{
	char	*buffer;
	char	*tmp;
	char	*segment;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (str[*i] && str[*i] != ' ' && operator_len(&str[*i]) == 0)
	{
		segment = process_segment(str, i, env_copy);
		if (!segment)
		{
			free(buffer);
			return (NULL);
		}
		tmp = append_and_free(buffer, segment);
		if (!tmp)
		{
			free(buffer);
			return (NULL);
		}
		buffer = tmp;
	}
	return (buffer);
}

int	handle_word(char *str, int *i, t_token **token_list, t_env *env_copy)
{
	char	*buffer;

	buffer = build_word_buffer(str, i, env_copy);
	if (!buffer)
	{
		g_status = 0;
		printf("WhatTheShell: syntax error: unclosed quote\n");
		return (0);
	}
	add_token_to_list(token_list, create_token(get_token_type_from_str(str),
			buffer));
	return (1);
}
