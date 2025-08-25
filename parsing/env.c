/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:51:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/25 22:26:13 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expansion prepare_expansion(char *token, char **env_copy)
{
	t_expansion exp;

	init_expansion(&exp);
	exp.dollar_pos = find_dollar(token);
	if (exp.dollar_pos == -1)
	{
		exp.result = ft_strdup(token);
		return exp;
	}
	exp.before = ft_substr(token, 0, exp.dollar_pos);
	exp.var_name = extract_var_name(token + exp.dollar_pos + 1);
	if (!exp.var_name)
	{
		free(exp.before);
		exp.result = ft_strdup(token);
		return exp;
	}
	exp.var_value = get_env_value(exp.var_name, env_copy);
	if (!exp.var_value)
		exp.var_value = "";

	exp.after = ft_strdup(token + exp.dollar_pos + 1 + ft_strlen(exp.var_name));
	exp.result = NULL;
	return exp;
}

char *build_expansion(t_expansion *exp)
{
	char *res;
	size_t total_len;

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

void expand_tokens(t_token *tokens, char **env_copy)
{
	t_expansion exp;
	char *expanded;

	while (tokens)
	{
		exp = prepare_expansion(tokens->value, env_copy);
		if (!exp.result)
			expanded = build_expansion(&exp);
		else
			expanded = exp.result;

		if (expanded)
		{
			free(tokens->value);
			tokens->value = expanded;
		}
		if (exp.before)
			free(exp.before);
		if (exp.var_name)
			free(exp.var_name);
		if (exp.after)
			free(exp.after);
		tokens = tokens->next;
	}
}
