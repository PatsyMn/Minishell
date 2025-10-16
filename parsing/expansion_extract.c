/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_extract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:50:30 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/16 11:46:56 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	extract_before_and_var(char *token, t_expansion *exp)
{
	exp->before = ft_substr(token, 0, exp->dollar_pos);
	if (!exp->before)
		return (false);
	char *var_start = token + exp->dollar_pos + 1;
	exp->var_name = extract_var_name(token + exp->dollar_pos + 1);
	if (*var_start == '\0' || *var_start == '>' || *var_start == '<' || *var_start == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		free(exp->before);
		return (false);
	}
	exp->var_name = extract_var_name(var_start);exp->var_name = extract_var_name(var_start);
	if (!exp->var_name || exp->var_name[0] == '\0')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		free(exp->before);
		if (exp->var_name)
			free(exp->var_name);
		return (false);
	}
	return (true);
}

bool	extract_var_value(t_expansion *exp, t_env *env_copy)
{
	if (ft_strncmp(exp->var_name, "?", 2) == 0)
	{
		exp->var_value = ft_itoa(g_status);
		if (!exp->var_value)
			return (false);
	}
	else
	{
		exp->var_value = my_getenv(env_copy, exp->var_name);
		if (!exp->var_value)
			exp->var_value = "";
	}
	return (true);
}

bool	extract_after(char *token, t_expansion *exp, t_env *env_copy)
{
	size_t	var_name_len;
	size_t	var_end_index;
	char	*after_start;

	if (!extract_var_value(exp, env_copy))
	{
		free(exp->before);
		free(exp->var_name);
		return (false);
	}
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
