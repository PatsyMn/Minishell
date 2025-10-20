/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_extract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:50:30 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 14:17:08 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	extract_before_and_var(char *token, t_expansion *exp)
{
	char	*var_start;

	exp->before = ft_substr(token, 0, exp->dollar_pos);
	if (!exp->before)
		return (false);
	var_start = token + exp->dollar_pos + 1;
	if (!check_var_syntax(var_start))
	{
		free(exp->before);
		exp->before = NULL;
		return (false);
	}
	if (!get_valid_var_name(var_start, exp))
	{
		free(exp->before);
		exp->before = NULL;
		return (false);
	}
	return (true);
}

bool	extract_var_value(t_expansion *exp, t_env *env_copy)
{
	char	*tmp;
	char	*env_val;

	if (ft_strncmp(exp->var_name, "?", 2) == 0)
	{
		tmp = ft_itoa(g_status);
		if (!tmp)
			return (false);
		exp->var_value = ft_strdup(tmp);
		free(tmp);
		if (!exp->var_value)
			return (false);
	}
	else
	{
		env_val = NULL;
		if (exp->var_name)
			env_val = my_getenv(env_copy, exp->var_name);
		if (!env_val)
			env_val = "";
		exp->var_value = ft_strdup(env_val);
		if (!exp->var_value)
			return (false);
	}
	return (true);
}

bool	set_exp_var_value(t_expansion *exp, t_env *env_copy)
{
	if (exp->var_name)
	{
		if (!extract_var_value(exp, env_copy))
		{
			free(exp->before);
			free(exp->var_name);
			return (false);
		}
	}
	else
	{
		exp->var_value = ft_strdup("");
		if (!exp->var_value)
			return (false);
	}
	return (true);
}

bool	extract_after(char *token, t_expansion *exp, t_env *env_copy)
{
	size_t	var_name_len;
	size_t	var_end_index;
	char	*after_start;

	var_name_len = 0;
	if (!set_exp_var_value(exp, env_copy))
		return (false);
	if (exp->var_name)
		var_name_len = ft_strlen(exp->var_name);
	var_end_index = (size_t)exp->dollar_pos + 1 + var_name_len;
	after_start = token + var_end_index;
	exp->after = ft_strdup(after_start);
	if (!exp->after)
	{
		free(exp->before);
		if (exp->var_name)
			free(exp->var_name);
		return (false);
	}
	return (true);
}
