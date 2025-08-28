/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:33:22 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/28 14:43:08 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== LIBRARIES ========== */
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

/* ========== TOKEN ========== */

typedef enum e_token_type
{
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WORD,
	T_COMMAND,
	T_PIPE,       // |
	T_REDIR_IN,   // <
	T_REDIR_OUT,  // >
	T_APPEND_OUT, // >>
	T_HEREDOC,    // <<
	T_FILENAME,
	T_DOLLAR_VAR,
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
	int				in_single_quote;
	int				in_double_quote;
}					t_quote_context;

// lexer_utils.c
char				**split_input_respecting_quotes(char *input);
void				free_split(char **split_input);
int					has_syntax_error_first_pipe(char **split_input);
int					check_syntax_operators(char **split_input);

// token_utils.c
t_token				*create_token(t_token_type type, char *str);
void				free_tokens(t_token *tokens);
void				add_token_to_list(t_token **head, t_token *new_token);

// lexer_check.c
int					is_double_quote(char *str);
int					is_single_quote(char *str);
int					check_unclosed_quotes(char *str);
int					check_special_chars(char *str);
// lexer_metachar.c
void				update_quote_context(t_quote_context *context, char c);
void				init_quote_context(t_quote_context *context);
char				*ft_strdup_with_escape(const char *input, int start,
						int end);

// lexer_tokenize.c
t_token				*tokenizer(char **split_input);
void				mark_commands(t_token *tokens);
char				**tokens_to_tab(t_token *tokens);
// debug
void				print_tokens(t_token *tokens);

typedef struct s_split_state
{
	char			**result;
	char			*input;
	t_quote_context	*context;
	int				start;
	int				i;
}					t_split_state;

/* ========== PARSER ========== */

typedef struct s_command
{
	char **args;            // argv style (cmd + args)
	char *infile;           // nom du fichier si '<'
	char *outfile;          // nom du fichier si '>'
	int append;             // 1 si >> (ajout)
	int heredoc;            // 1 si <<
	struct s_command *next; // chaînage pour les pipes
}					t_command;

typedef struct s_expansion
{
	int				dollar_pos;
	char			*var_name;
	char			*var_value;
	char			*before;
	char			*after;
	char			*result;
	char			*expanded;
}					t_expansion;

// init.c
void				init_expansion(t_expansion *exp);

// parser.c
t_command			*new_command(void);
t_command			*parser(t_token *token);
// debug
void				print_commands(t_command *cmd);
void				free_commands(t_command *cmd);

// parser_utils.c
char				*remove_quotes(char *str);
void				add_arg(t_command *cmd, char *val);
void				handle_redirection(t_command *cmd, t_token **token);

// env_utils.c
char				**copy_env(char **envp);
char				*get_env_value(char *var_name, char **env_copy);
int					find_dollar(char *str);
char				*extract_var_name(char *str);
void				free_env(char **env);

// env.c
char				*strip_outer_single_quotes(const char *token);
char				*strip_outer_double_quotes(const char *token);
t_expansion			prepare_expansion(char *token, char **env_copy);
char				*build_expansion(t_expansion *exp);
void				expand_tokens(t_token *tokens, char **env_copy);

#endif
