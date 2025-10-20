/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:06:02 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 18:34:23 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(t_token_type type, char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(str);
		return (NULL);
	}
	if (!str || str[0] == '\0')
	{
		free(str);
		str = ft_strdup("");
	}
	token->type = type;
	token->value = str;
	token->next = NULL;
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	new_token->next = NULL;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
