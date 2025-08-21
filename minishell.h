/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:33:22 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/21 15:47:39 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "Libft/libft.h"

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
char				**split_input_respecting_quotes(char *input);
void				free_split(char **split_input);

// token_utils.c
t_token				*create_token(t_token_type type, char *str);
void				free_tokens(t_token *tokens);
void				add_token_to_list(t_token **head, t_token *new_token);
int					count_tokens(t_token *tokens);

// lexer_check.c
int					check_unclosed_quotes(char *str);
int					check_special_chars(char *str);
// lexer_metachar.c
void	update_quote_context(t_quote_context *context, char c);
void	init_quote_context(t_quote_context *context);
char	*ft_strndup(const char *s, size_t n);


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









/* ========== COLORS ========== */

#ifndef COLORS_H
# define COLORS_H

// Reset
# define RESET       "\033[0m"

// Regular Colors
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define PURPLE      "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// Bold Colors
# define BBLACK      "\033[1;30m"
# define BRED        "\033[1;31m"
# define BGREEN      "\033[1;32m"
# define BYELLOW     "\033[1;33m"
# define BBLUE       "\033[1;34m"
# define BPURPLE     "\033[1;35m"
# define BCYAN       "\033[1;36m"
# define BWHITE      "\033[1;37m"

// Underline Colors
# define UBLACK      "\033[4;30m"
# define URED        "\033[4;31m"
# define UGREEN      "\033[4;32m"
# define UYELLOW     "\033[4;33m"
# define UBLUE       "\033[4;34m"
# define UPURPLE     "\033[4;35m"
# define UCYAN       "\033[4;36m"
# define UWHITE      "\033[4;37m"

// Background Colors
# define ONBLACK     "\033[40m"
# define ONRED       "\033[41m"
# define ONGREEN     "\033[42m"
# define ONYELLOW    "\033[43m"
# define ONBLUE      "\033[44m"
# define ONPURPLE    "\033[45m"
# define ONCYAN      "\033[46m"
# define ONWHITE     "\033[47m"

#endif