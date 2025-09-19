/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:01:47 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/19 15:49:33 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_filename_types(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if ((curr->type == T_REDIR_OUT || curr->type == T_APPEND_OUT
				|| curr->type == T_REDIR_IN || curr->type == T_HEREDOC)
			&& curr->next && curr->next->type == T_WORD)
		{
			curr->next->type = T_FILENAME;
		}
		curr = curr->next;
	}
}
