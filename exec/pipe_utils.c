/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:39:12 by mbores            #+#    #+#             */
/*   Updated: 2025/10/14 14:52:56 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void safe_close(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

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
