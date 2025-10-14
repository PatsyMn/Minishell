/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:39:12 by mbores            #+#    #+#             */
/*   Updated: 2025/10/14 13:05:21 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_token(t_token *token_list, t_token_type type)
{
	while (token_list)
	{
		if (token_list->type == type)
			return (token_list->value);
		token_list = token_list->next;
	}
	return (NULL);
}
