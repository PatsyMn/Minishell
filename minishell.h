/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:33:22 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 15:50:32 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== LIBRARIES ========== */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "Libft/libft.h"

/* ========== TOKEN ========== */

typedef enum e_token_type
{
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WORD, //cmd ou arg
	T_PIPE, // |
	T_REDIR_IN, // <
	T_REDIR_OUT, // >
	T_APPEND_OUT, // >>
	T_HEREDOC, // << 
	T_FILENAME,
	T_DOLLAR, 
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* ========== LEXER ========== */

typedef struct s_quote_context
{
	int in_single_quote;
	int in_double_quote;
}					t_quote_context;

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
//debug
void	print_tokens(t_token *tokens);

typedef struct s_split_state
{
	char			**result;
	char			*input;
	t_quote_context	*context;
	int				start;
	int				i;
}	t_split_state;


/* ========== PARSER ========== */

typedef struct s_command
{
	char	**args;            // argv style (cmd + args)
	char	*infile;           // nom du fichier si '<'
	char	*outfile;          // nom du fichier si '>'
	int		append;            // 1 si >> (ajout)
	int		heredoc;           // 1 si <<
	struct s_command *next;    // chaînage pour les pipes
}	t_command;

//parser.c
t_command	*new_command(void);
t_command	*parser(t_token *token);
//debug
void	print_commands(t_command *cmd);




#endif

