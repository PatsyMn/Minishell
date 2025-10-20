/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:01:47 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 16:12:17 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_filename_types(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_HEREDOC && current->next
			&& current->next->type == T_WORD)
			current->next->type = T_DELIMITER;
		else if ((current->type == T_REDIR_OUT || current->type == T_APPEND_OUT
				|| current->type == T_REDIR_IN)
			&& current->next && (current->next->type == T_WORD
				|| current->next->type == T_DOUBLE_QUOTE
				|| current->next->type == T_SINGLE_QUOTE))
			current->next->type = T_FILENAME;
		current = current->next;
	}
}
