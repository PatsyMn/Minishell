/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:39:12 by mbores            #+#    #+#             */
/*   Updated: 2025/10/03 17:55:40 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infiles_outfiles(t_token *token_list)
{
	int	fd;

	while (token_list)
	{
		if (token_list->type == T_REDIR_IN)
		{
			fd = open(token_list->next->value, O_RDONLY);
			if (fd == -1)
			{
				g_status = 1;
				write(STDERR_FILENO, "minishell: permission denied: ", 30);
				write(STDERR_FILENO, token_list->next->value,
					ft_strlen(token_list->next->value));
				return ;
			}
			close(fd);
		}
	}
}

t_token	*find_token(t_token *token_list, t_token_type *type)
{
	while (token_list)
	{
		if (token_list->type == type)
			return (token_list);
		token_list = token_list->next;
	}
	return (NULL);
}
