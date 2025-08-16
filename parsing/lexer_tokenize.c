/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/16 15:13:02 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char c)
{
	if (c == '\'')
		return (T_SINGLE_QUOTE);
	if (c == '"')
		return (T_DOUBLE_QUOTE);
	if (c == '|')
		return (T_PIPE);
	return (T_WORD);
}
static t_token_type	get_token_type_from_str(char *str)
{
	if (str[0] == '|' && str[1] == '\0')
		return (T_PIPE);
	return (T_WORD);
}
//prend en entrée un tableau de chaînes de caractères (line_tab) = résultat de la fonction ft_split qui a séparé une ligne de commande en mots
t_token	*tokenizer(char **line_tab)
{
	t_token	*token_list = NULL;
	t_token	*new_token = NULL;
	int		i = 0;

	while (line_tab[i])
	{
		t_token_type type = get_token_type_from_str(line_tab[i]);
		new_token = create_token(type, strdup(line_tab[i]));
		add_token_to_list(&token_list, new_token);
		i++;
	}
	return (token_list);
}

