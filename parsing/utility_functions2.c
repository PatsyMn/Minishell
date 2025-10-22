/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:04:20 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/21 16:47:02 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_token_type_2(t_token_type type)
{
	if (type == T_HEREDOC)
		write(1, "T_HEREDOC", 9);
	else if (type == T_INVALID_OPERATOR)
		write(1, "T_INVALID_OPERATOR", 18);
	else if (type == T_FILENAME)
		write(1, "T_FILENAME", 10);
	else if (type == T_DELIMITER)
		write(1, "T_DELIMITER", 11);
	else if (type == T_DOLLAR_VAR)
		write(1, "T_DOLLAR_VAR", 12);
	else
		write(1, "UNKNOWN", 7);
}

static void	print_token_type_1(t_token_type type)
{
	if (type == T_SINGLE_QUOTE)
		write(1, "T_SINGLE_QUOTE", 14);
	else if (type == T_DOUBLE_QUOTE)
		write(1, "T_DOUBLE_QUOTE", 14);
	else if (type == T_WORD)
		write(1, "T_WORD", 6);
	else if (type == T_COMMAND)
		write(1, "T_COMMAND", 9);
	else if (type == T_PIPE)
		write(1, "T_PIPE", 6);
	else if (type == T_REDIR_IN)
		write(1, "T_REDIR_IN", 10);
	else if (type == T_REDIR_OUT)
		write(1, "T_REDIR_OUT", 11);
	else if (type == T_APPEND_OUT)
		write(1, "T_APPEND_OUT", 12);
	else
		print_token_type_2(type);
}

void	print_token_list(t_token *list)
{
	while (list)
	{
		write(1, "Type: ", 6);
		print_token_type_1(list->type);
		write(1, " | Value: ", 10);
		if (list->value)
			write(1, list->value, ft_strlen(list->value));
		else
			write(1, "(null)", 6);
		write(1, "\n", 1);
		list = list->next;
	}
}

int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
