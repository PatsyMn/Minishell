/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:35:10 by mbores            #+#    #+#             */
/*   Updated: 2025/09/29 19:57:42 by pmeimoun         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>


typedef enum e_token_type
{
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WORD,
	T_COMMAND,
	T_PIPE,			// |
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_APPEND_OUT,	// >>
	T_HEREDOC,		// <<
	T_INVALID_OPERATOR,
	T_FILENAME,
	T_DOLLAR_VAR,
}						t_token_type;

typedef struct s_pipex
{
	pid_t	pid;
	pid_t	last_pid;
	int		pipe;
	int		input_fd;
	int		pipe_fd[2];
	int		cmd_count;
	int		status;
	int		last_status;
	int		saved_stdin;
	int		saved_stdout;
}						t_pipex;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_input
{
	const char	*str;
	int			index;
	int			end;
}	t_input;

typedef struct s_output
{
	char	*str;
	int		index;
}	t_output;

typedef struct s_command
{
	char				**args;		// argv style (cmd + args)
	char				*infile;	// nom du fichier si '<'
	char				*outfile;	// nom du fichier si '>'
	char				*limiter;
	int					infile_fd;
	int					outfile_fd;
	int					heredoc_file_fd;
	int					append;		// 1 si >> (ajout)
	int					heredoc;	// 1 si <<
	struct s_command	*next;		// chaînage pour les pipes
}						t_command;

typedef struct s_expansion
{
	int					dollar_pos;
	char				*var_name;
	char				*var_value;
	char				*before;
	char				*after;
	char				*result;
	char				*expanded;
}						t_expansion;

typedef struct s_quote_context
{
	int					in_single_quote;
	int					in_double_quote;
}						t_quote_context;

typedef enum e_quote_state
{
	NO_QUOTE = 0,
	IN_SINGLE = 1,
	IN_DOUBLE = 2,
}	t_quote_state;


typedef struct s_split_state
{
	char				**result;
	char				*input;
	t_quote_context		*context;
	int					start;
	int					i;
}						t_split_state;

typedef struct s_env
{
	char				*key;
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct s_export
{
	t_env				*env;
	t_env				*export;
}						t_export;

/* ========== LEXER ========== */

//lexer_utils.c
int						count_tokens(t_token *tokens);
int						check_invalid_tokens(t_token *token_list);
void					mark_commands(t_token *tokens);

//token_utils.c
t_token					*create_token(t_token_type type, char *str);
void					free_tokens(t_token *tokens);
void					add_token_to_list(t_token **head, t_token *new_token);

//lexer_check_quotes.c
int						is_double_quote(char *str);
int						is_single_quote(char *str);
int						check_unclosed_quotes(char *str);

//lexer_check_.c
int						check_special_chars(char *str);
int						is_special_single_char(char *input);

//lexer_metachar.c
void					update_quote_context(t_quote_context *context, char c);
void					init_quote_context(t_quote_context *context);

//lexer_split_str.c
char							**split_input_respecting_quotes(char *input);
void							free_split(char **split_input);

//lexer_split_word_utils.c
char							**split_and_add_word(t_split_state *state);
char							**add_word_to_tab(char **tab, char *word);
int								handle_split_word(t_split_state *state);

//lexer_split_loop.c
char							**split_loop(t_split_state *state);

//lexer_split_loop_utils.c
void							handle_redirect(t_split_state *state);
void							handle_pipe(t_split_state *state);
void							handle_space_or_end(t_split_state *state);

//utiliy_functions.c
char					*ft_strdup_with_escape(const char *input, int start, int end);

//utiliy_functions2.c
int						is_operator_char(char c);

//lexer_operator.c
int						operator_length(char *str);
int						is_invalid_operator(char *str);
int						handle_operator(char *str, int *i, t_token **token_list);

//lexer_errors.c
int						has_syntax_error_first_pipe(char **split_input);
int						has_syntax_error_last_pipe(char **split_input);
int						has_syntax_error_ampersand(char **split_input);

//lexer_errors_operators.c
int						check_syntax_operators(char **split_input);

//lexer_word.c
int						handle_word(char *str, int *i, t_token **token_list, t_env *env_copy);

//lexer_files.c
void					assign_filename_types(t_token *tokens);

// lexer_tokenize.c
t_token_type			get_token_type_from_str(char *str);
t_token					*tokenizer(char **split_input, t_env *env_copy);
char					**tokens_to_tab(t_token *tokens);
//debug
void					print_tokens(t_token *tokens);

/* ========== PARSER ========== */

//init.c
void							init_expansion(t_expansion *exp);

//parser.c
t_command						*parser(t_token *token, t_pipex *pipex);
//debug
void							print_commands(t_command *cmd);

//parser_utils.c
void							add_arg(t_command *cmd, char *val);
void							free_commands(t_command *cmd);

//parser_redirections.c
void							handle_redirection(t_command *cmd, t_token **token);

//quote_utils.c
char							*strip_outer_single_quotes(const char *token);
char							*strip_outer_double_quotes(const char *token);

//env_utils.c
t_env							*new_env_node(char *str);
t_env							*copy_env_chained(char **envp);
void							free_env_chained(t_env *env);
void							free_env(char **env);
// char							**copy_env(char **envp);
// char							*get_env_value(char *var_name, char **env_copy);

//expansion_utils.c
int								find_dollar(char *str);
char							*extract_var_name(char *str);
char							*build_expansion(t_expansion *exp);
char							*clean_and_strip_token(char *token);
void							free_exp(t_expansion *exp);

//expand_tokens.c
void							expand_tokens(t_token *tokens, t_env *env_copy);

//expension_preparation.c
char							*expand_variables(char *str, t_env *env_copy);
t_expansion						prepare_expansion(char *token, t_env *env_copy);

/* ========== SIGNALS ========== */

extern sig_atomic_t	g_status;
void							handle_signal_prompt(int sig);
void							setup_signals_exec(void);
void							child_signal(int status);

// execute_cmd.c
int 					execute_cmd(t_env *envp, t_command *commands);
char					**env_list_to_tab(t_env *env);

// pipe_handle.c
// void    				close_all_fds(t_pipex *pipex, t_command *command);
void	   				child_process(t_command *command, t_pipex *pipex, t_export *export);

// open_files.c
void    				open_files(t_command *command);

// builtin_utils.c
void    				sort_env_tab(char **env_tab);

// builtin.c
int 					execute_builtin(t_command *command, t_export *export, t_pipex *pipex, int status);

// builtin_export.c
void    				new_export(t_export *export, t_command *command);
int 					builtin_export(t_export *export, t_command *command);

// builtin_echo.c
int 					builtin_echo(char **args);

// builtin_env.c
int 					builtin_env(t_env *env);

// builtin_pwd.c
int 					builtin_pwd(t_env *env);

// builtin_unset.c
int 					builtin_unset(t_export *export, t_command *command);

// builtin_cd.c
int 					builtin_cd(t_command *command, t_env **env);

// builtin_exit.c
int 					builtin_exit(t_command *command, int status);

// env_handle.c
char    				*my_getenv(t_env *env, char *var);
void    				my_setenv(t_env **env, char *var, char *content);

#endif


/* ========== COLORS ========== */

//prompt
#define RESET	"\033[0m"
#define PINK "\033[1;38;2;255;20;147m"



