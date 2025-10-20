/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:04:20 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 15:43:02 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

// static char	*token_type_to_str(t_token_type type)
// {
// 	if (type == T_SINGLE_QUOTE)
// 		return ("T_SINGLE_QUOTE");
// 	if (type == T_DOUBLE_QUOTE)
// 		return ("T_DOUBLE_QUOTE");
// 	if (type == T_WORD)
// 		return ("T_WORD");
// 	if (type == T_COMMAND)
// 		return ("T_COMMAND");
// 	if (type == T_PIPE)
// 		return ("T_PIPE");
// 	if (type == T_REDIR_IN)
// 		return ("T_REDIR_IN");
// 	if (type == T_REDIR_OUT)
// 		return ("T_REDIR_OUT");
// 	if (type == T_APPEND_OUT)
// 		return ("T_APPEND_OUT");
// 	if (type == T_HEREDOC)
// 		return ("T_HEREDOC");
// 	if (type == T_INVALID_OPERATOR)
// 		return ("T_INVALID_OPERATOR");
// 	if (type == T_FILENAME)
// 		return ("T_FILENAME");
// 	if (type == T_DELIMITER)
// 		return ("T_DELIMITER");
// 	if (type == T_DOLLAR_VAR)
// 		return ("T_DOLLAR_VAR");
// 	return ("UNKNOWN");
// }

// void	print_token_list(t_token *list)
// {
// 	t_token	*tmp;

// 	tmp = list;
// 	printf("=== TOKEN LIST ===\n");
// 	while (tmp)
// 	{
// 		printf("type: %-20s | value: '%s'\n",
// 			token_type_to_str(tmp->type),
// 			tmp->value ? tmp->value : "(null)");
// 		tmp = tmp->next;
// 	}
// 	printf("==================\n");
// }
