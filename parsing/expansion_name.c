/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:08:13 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 14:48:38 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_var_syntax(char *var_start)
{
	if (!var_start || ft_strncmp(var_start, ">>", 2) == 0
		|| ft_strncmp(var_start, "<<", 2) == 0 || *var_start == '<'
		|| *var_start == '|')
	{
		printf("WhatTheShell: syntax error near ");
		printf("unexpected token `newline'\n");
		return (false);
	}
	return (true);
}

bool	get_valid_var_name(char *var_start, t_expansion *exp)
{
	if (var_start[0] == '"' && var_start[1] == '"')
	{
		exp->var_name = NULL;
		return (true);
	}
	if (!ft_isalpha(*var_start) && *var_start != '_' && *var_start != '?'
		&& !ft_isdigit(*var_start))
	{
		exp->var_name = NULL;
		return (true);
	}
	exp->var_name = extract_var_name(var_start);
	if (!exp->var_name || exp->var_name[0] == '\0')
	{
		printf("WhatTheShell: syntax error near ");
		printf("unexpected token `newline'\n");
		return (false);
	}
	return (true);
}
