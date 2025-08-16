/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:33:22 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/16 14:21:24 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries
#include <stdio.h>

// Token types
typedef enum e_token_type
{
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WORD,
	T_PIPE,
}					t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}					t_token;

// Quote context for parsing
typedef struct s_quote_context
{
	int in_single_quote;
	int in_double_quote;
}					t_quote_context;


/* ========== LEXER FUNCTIONS ========== */

// token_utils.c
t_token				*create_token(t_token_type type, char *str);
void				free_tokens(t_token *tokens);
void				add_token_to_list(t_token **head, t_token *new_token);
int					count_tokens(t_token *tokens);



/* ========== PARSER FUNCTIONS ========== */




#endif
