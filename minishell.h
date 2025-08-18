/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:33:22 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/18 15:03:35 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries
#include <stdio.h>
#include <stdlib.h>

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

// lexer_utils.c
char	**split_input_respecting_quotes(char *input)

// token_utils.c
t_token				*create_token(t_token_type type, char *str);
void				free_tokens(t_token *tokens);
void				add_token_to_list(t_token **head, t_token *new_token);
int					count_tokens(t_token *tokens);

// lexer_check.c
int					check_unclosed_quotes(char *str);
int					check_special_chars(char *str);

// lexer_metachar.c


// lexer_tokenize.c
t_token	*tokenizer(char **split_input);

typedef struct s_split_state
{
	char			**result;
	char			*input;
	t_quote_context	*context;
	int				start;
	int				i;
}	t_split_state;


/* ========== PARSER FUNCTIONS ========== */




#endif
