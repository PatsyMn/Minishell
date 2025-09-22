/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:19:10 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/17 14:42:18 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	operator_length(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (str[i] == '>' || str[i] == '<')
	{
		c = str[i];
		while (str[i] && str[i] == c)
			i++;
		if (str[i] == '>' || str[i] == '<')
			return (-1);
		if (i > 2)
			return (-1);
		return (i);
	}
	else if (str[i] == '|')
	{
		while (str[i] && str[i] == '|')
			i++;
		if (i > 1)
			return (-1);
		return (i);
	}
	return (0);
}

int	is_invalid_operator(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	if (len > 2)
	{
		while (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			i++;
		if (i == len)
			return (1);
	}
	if (len == 2 && !ft_strncmp(str, "||", 3))
		return (1);
	return (0);
}

int	handle_operator(char *str, int *i, t_token **token_list)
{
	int		op_len;
	char	*sub;

	op_len = operator_length(&str[*i]);
	if (op_len == -1)
	{
		sub = ft_substr(str, *i, 2);
		if (!sub)
			return (-1);
		add_token_to_list(token_list, create_token(T_INVALID_OPERATOR, sub));
		*i += ft_strlen(sub);
		return (1);
	}
	if (op_len <= 0)
		return (0);
	sub = ft_substr(str, *i, op_len);
	if (!sub)
		return (-1);
	add_token_to_list(token_list, create_token(get_token_type_from_str(sub),
			sub));
	*i += op_len;
	return (1);
}
