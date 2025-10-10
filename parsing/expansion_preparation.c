/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_preparation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:51:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/10 15:09:59 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	extract_before_and_var(char *token, t_expansion *exp)
{
	exp->before = ft_substr(token, 0, exp->dollar_pos);
	if (!exp->before)
		return (false);
	exp->var_name = extract_var_name(token + exp->dollar_pos + 1);
	if (!exp->var_name)
	{
		free(exp->before);
		exp->before = NULL;
		return (false);
	}
	return (true);
}

static bool	extract_after(char *token, t_expansion *exp, t_env *env_copy)
{
	size_t	var_name_len;
	size_t	var_end_index;
	char	*after_start;

	if (ft_strncmp(exp->var_name, "?", 2) == 0)
	{
		exp->var_value = ft_itoa(g_status);
		if (!exp->var_value)
		{
			free(exp->before);
			free(exp->var_name);
			return (false);
		}
	}
	else
	exp->var_value = my_getenv(env_copy, exp->var_name);
	if (!exp->var_value)
		exp->var_value = "";
	var_name_len = ft_strlen(exp->var_name);
	var_end_index = (size_t)exp->dollar_pos + 1 + var_name_len;
	after_start = token + var_end_index;
	exp->after = ft_strdup(after_start);
	if (!exp->after)
	{
		free(exp->before);
		free(exp->var_name);
		return (false);
	}
	return (true);
}

static bool	handle_dollar(char *token, t_expansion *exp, t_env *env_copy)
{
	exp->dollar_pos = find_dollar(token);
	if (exp->dollar_pos == -1)
	{
		exp->result = ft_strdup(token);
		return (false);
	}
	if (!extract_before_and_var(token, exp))
	{
		exp->result = ft_strdup(token);
		return (false);
	}
	if (!extract_after(token, exp, env_copy))
	{
		exp->result = ft_strdup(token);
		return (false);
	}
	exp->result = NULL;
	return (true);
}

t_expansion	prepare_expansion(char *token, t_env *env_copy)
{
	t_expansion	exp;
	char		*clean_token;

	init_expansion(&exp);
	clean_token = clean_and_strip_token(token);
	if (!clean_token)
		return (exp);
	if (!handle_dollar(clean_token, &exp, env_copy))
	{
		free(clean_token);
		return (exp);
	}
	free(clean_token);
	return (exp);
}

char	*expand_variables(char *str, t_env *env_copy)
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
