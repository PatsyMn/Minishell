/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:51:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/10 16:29:46 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expansion	prepare_expansion(char *token, char **env_copy)
{
	t_expansion	exp;
	char		*tmp;

	init_expansion(&exp);
	tmp = ft_strdup(token);
	if (!tmp)
		return (exp);
	token = strip_outer_double_quotes(tmp);
	free(tmp);
	if (!token)
		return (exp);
	exp.dollar_pos = find_dollar(token);
	if (exp.dollar_pos == -1)
	{
		exp.result = ft_strdup(token);
		free(token);
		return (exp);
	}
	exp.before = ft_substr(token, 0, exp.dollar_pos);
	exp.var_name = extract_var_name(token + exp.dollar_pos + 1);
	if (!exp.var_name)
	{
		free(exp.before);
		exp.result = ft_strdup(token);
		free(token);
		return (exp);
	}
	exp.var_value = get_env_value(exp.var_name, env_copy);
	if (!exp.var_value)
		exp.var_value = "";
	exp.after = ft_strdup(token + exp.dollar_pos + 1 + ft_strlen(exp.var_name));
	exp.result = NULL;
	free(token);
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

void	free_exp(t_expansion *exp)
{
	if (exp->before)
		free(exp->before);
	if (exp->var_name)
		free(exp->var_name);
	if (exp->after)
		free(exp->after);
	if (exp->result)
		free(exp->result);
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
			free_exp(&exp);
		}
		else if (tokens->type == 0)
		{
			char *tmp = tokens->value;
			tokens->value = strip_outer_double_quotes(tokens->value);
			if (tmp != tokens->value)
				free(tmp);
		}
		tokens = tokens->next;
	}
}

char	*expand_variables(char *str, char **env_copy)
{
	t_expansion	exp;
	char		*expanded;

	exp = prepare_expansion(str, env_copy);
	if (exp.result)
	{
		expanded = ft_strdup(exp.result);
		free_exp(&exp);
		return (expanded);
	}
	expanded = build_expansion(&exp);
	free_exp(&exp);
	return (expanded);
}

