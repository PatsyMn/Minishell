/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:46:10 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/10 15:20:11 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_var_name(char *str)
{
	int		i;
	char	*var_name;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (NULL);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	var_name[i] = '\0';
	while (--i >= 0)
		var_name[i] = str[i];
	return (var_name);
}

char	*clean_and_strip_token(char *token)
{
	char	*tmp;
	char	*stripped;

	tmp = ft_strdup(token);
	if (!tmp)
		return (NULL);
	stripped = strip_outer_double_quotes(tmp);
	free(tmp);
	return (stripped);
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
	{
		free(exp->before);
		exp->before = NULL;
	}
	if (exp->var_name)
	{
		free(exp->var_name);
		exp->var_name = NULL;
	}
	if (exp->after)
	{
		free(exp->after);
		exp->after = NULL;	
	}
	if (exp->result)
	{
		free(exp->result);
		exp->result = NULL;	
	}
}
