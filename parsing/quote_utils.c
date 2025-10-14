/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:33:27 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/14 23:54:43 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*char	*strip_outer_single_quotes(const char *token)
{
	size_t	len;
	char	*new_str;

	if (!token)
		return (NULL);
	len = ft_strlen(token);
	if (len >= 2 && token[0] == '\'' && token[len - 1] == '\'')
	{
		new_str = malloc(len - 1);
		if (!new_str)
			return (NULL);
		ft_memcpy(new_str, token + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (ft_strdup(token));
}*/

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
		ft_memcpy(new_str, token + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (ft_strdup(token));
}
