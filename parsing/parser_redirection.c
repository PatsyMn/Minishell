/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:29:50 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 12:18:44 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_redirection(t_token **token)
{
	if (!token || !(*token))
		return ;
	if ((*token)->next)
		*token = (*token)->next->next;
	else
		*token = NULL;
}
