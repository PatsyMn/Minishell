/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/15 22:23:25 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*

Séparer les éléments avec les "espace" pour avoir toutes les instruction.

Exemple :
ls | wc -l
Ici nous avons 4 éléments :

1 : ls

1 : |

1 : wc

1 : -l */

static char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
		str++;
	return (str);
}

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





t_token	*tokenize()
{

}
