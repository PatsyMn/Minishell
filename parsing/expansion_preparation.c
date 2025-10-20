/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_preparation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:51:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 16:19:55 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	handle_dollar(char *token, t_expansion *exp, t_env *env_copy)
{
	exp->dollar_pos = find_dollar(token);
	if (exp->dollar_pos == -1 || (exp->dollar_pos == 0 && !token[exp->dollar_pos
			+ 1]))
	{
		free_exp(exp);
		exp->result = ft_strdup(token);
		return (false);
	}
	if (!extract_before_and_var(token, exp))
	{
		free_exp(exp);
		exp->result = ft_strdup(token);
		return (false);
	}
	if (!extract_after(token, exp, env_copy))
	{
		free_exp(exp);
		exp->result = ft_strdup(token);
		return (false);
	}
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

	expanded = NULL;
	init_expansion(&exp);
	while (!exp.result)
	{
		free(expanded);
		expanded = build_expansion(&exp);
		if (expanded)
			str = expanded;
		free_exp(&exp);
		init_expansion(&exp);
		handle_dollar(str, &exp, env_copy);
	}
	free(expanded);
	expanded = ft_strdup(exp.result);
	free_exp(&exp);
	return (expanded);
}
