/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:51:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/27 17:14:00 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strip_outer_double_quotes(const char *token)
{
	size_t	len;
	char	*new_str;

	if (!token)
		return (NULL);
	len = ft_strlen(token);
	if (len >= 2 && token[0] == '"' && token[len - 1] == '"')
	{
		new_str = malloc(len - 1);
		if (!new_str)
			return (NULL);
		memcpy(new_str, token + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (strdup(token));
}

t_expansion	prepare_expansion(char *token, char **env_copy)
{
	t_expansion	exp;

	init_expansion(&exp);
	token = strip_outer_double_quotes(token);
	exp.dollar_pos = find_dollar(token);
	if (exp.dollar_pos == -1)
	{
		exp.result = ft_strdup(token);
		return (exp);
	}
	exp.before = ft_substr(token, 0, exp.dollar_pos);
	exp.var_name = extract_var_name(token + exp.dollar_pos + 1);
	if (!exp.var_name)
	{
		free(exp.before);
		exp.result = ft_strdup(token);
		return (exp);
	}
	exp.var_value = get_env_value(exp.var_name, env_copy);
	if (!exp.var_value)
		exp.var_value = "";
	exp.after = ft_strdup(token + exp.dollar_pos + 1 + ft_strlen(exp.var_name));
	exp.result = NULL;
	return (exp);
}

char	*build_expansion(t_expansion *exp)
{
	char	*res;
	size_t	total_len;

	total_len = ft_strlen(exp->before) + ft_strlen(exp->var_value)
		+ ft_strlen(exp->after) + 1;
	res = malloc(total_len);
	if (!res)
		return (NULL);
	res[0] = '\0';
	ft_strlcat(res, exp->before, total_len);
	ft_strlcat(res, exp->var_value, total_len);
	ft_strlcat(res, exp->after, total_len);
	return (res);
}

void	expand_tokens(t_token *tokens, char **env_copy)
{
	t_expansion	exp;

	while (tokens)
	{
		if (tokens->type == 1)
		{
			exp = prepare_expansion(tokens->value, env_copy);
			if (!exp.result)
				exp.expanded = build_expansion(&exp);
			else
				exp.expanded = exp.result;
			if (exp.expanded)
			{
				free(tokens->value);
				tokens->value = exp.expanded;
			}
			if (exp.before)
				free(exp.before);
			if (exp.var_name)
				free(exp.var_name);
			if (exp.after)
				free(exp.after);
		}
		tokens = tokens->next;
	}
}
