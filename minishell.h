/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:35:10 by mbores            #+#    #+#             */
/*   Updated: 2025/10/15 10:46:46 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== LIBRARIES ========== */
# include "Libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WORD,
	T_COMMAND,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND_OUT,
	T_HEREDOC,
	T_INVALID_OPERATOR,
	T_FILENAME,
	T_DELIMITER,
	T_DOLLAR_VAR,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				**args;
	t_token				*token_list;
	struct s_command	*next;
}						t_command;

typedef struct s_pipex
{
	pid_t				pid;
	pid_t				last_pid;
	int					pipe;
	int					input_fd;
	int					output_fd;
	int					pipe_fd[2];
	int					cmd_count;
	int					status;
	int					last_status;
	int					saved_stdin;
	int					saved_stdout;
	int					n;
	t_command			*commands_head;
}						t_pipex;

typedef struct s_input
{
	const char			*str;
	int					index;
	int					end;
}						t_input;

typedef struct s_output
{
	char				*str;
	int					index;
}						t_output;

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
	NO_QUOTE,
	IN_SINGLE,
	IN_DOUBLE,
}						t_quote_state;

typedef struct s_split_state
{
	char				**result;
	char				*input;
	t_quote_context		*context;
	int					start;
	int					i;
}						t_split_state;

typedef struct s_command_split_context
{
	t_command			*head;
	t_command			*current;
	t_token				*last_token_copy;
	t_token				*new_token_copy;
	t_command			*tmp;
}						t_command_split_context;

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

typedef struct s_shell
{
	char		*input;
	const char	*prompt;
	int			ret;
	t_export	*export;
}	t_shell;

// main.c
void					wait_child(void);
int						init_pipex(t_pipex *pipex, t_command *commands);

/* ========== LEXER ========== */

// input_handler.c
int						handle_input(char *input, t_export *export);

// lexer_utils.c
int						count_tokens(t_token *tokens);
int						check_invalid_tokens(t_token *token_list);
void					detect_command_tokens(t_token *tokens);

// token_utils.c
t_token					*create_token(t_token_type type, char *str);
void					free_tokens(t_token *tokens);
void					add_token_to_list(t_token **head, t_token *new_token);

// lexer_check_quotes.c
int						is_double_quote(char *str);
int						is_single_quote(char *str);
int						check_unclosed_quotes(char *str);

// lexer_check_.c
int						check_special_chars(char *str);
int						is_special_single_char(char *input);

// lexer_metachar.c
void					update_quote_context(t_quote_context *context, char c);
void					init_quote_context(t_quote_context *context);

// lexer_split_str.c
char					**split_input_respecting_quotes(char *input);
void					free_split(char **split_input);

// lexer_split_word_utils.c
char					**split_and_add_word(t_split_state *state);
char					**add_word_to_tab(char **tab, char *word);
int						handle_split_word(t_split_state *state);

// lexer_split_loop.c
char					**split_loop(t_split_state *state);

// lexer_split_loop_utils.c
void					handle_redirection(t_split_state *state);
void					handle_pipe(t_split_state *state);
void					handle_space_or_end(t_split_state *state);

// utiliy_functions.c
char					*ft_strdup_with_escape(const char *input, int start,
							int end);

// utiliy_functions2.c
int						is_operator_char(char c);

// lexer_operator.c
int						operator_len(char *str);
int						is_invalid_operator(char *str);
int						handle_operator(char *str, int *i,
							t_token **token_list);

// lexer_errors.c
int						has_syntax_error_first_pipe(char **split_input);
int						has_syntax_error_last_pipe(char **split_input);
int						has_syntax_error_ampersand(char **split_input);

// lexer_errors_operators.c
int						check_syntax_operators(char **split_input);

// lexer_word.c
int						handle_word(char *str, int *i, t_token **token_list,
							t_env *env_copy);

// lexer_files.c
void					assign_filename_types(t_token *tokens);

// lexer_tokenize.c
t_token_type			get_token_type_from_str(char *str);
t_token					*tokenizer(char **split_input, t_env *env_copy);
char					**tokens_to_tab(t_token *tokens);
// debug
void					print_tokens(t_token *tokens);

/* ========== PARSER ========== */

// init.c
void					init_expansion(t_expansion *exp);

// parser.c
void					build_args(t_command *cmd);
t_command				*parser(t_token *tokens);
// debug
void					print_commands(t_command *cmd);

// command_split.c
t_command				*split_token_list(t_token *token_list);

// parser_utils.c
void					add_arg(t_command *cmd, char *val);
void					free_commands(t_command *cmd);

// quote_utils.c
//char					*strip_outer_single_quotes(const char *token);
char					*strip_outer_double_quotes(const char *token);

// env_utils.c
t_env					*new_env_node(char *str);
t_env					*copy_env_chained(char **envp);
void					free_env_chained(t_env *env);
void					free_env(char **env);
// char							**copy_env(char **envp);
// char							*get_env_value(char *var_name, char **env_copy);

// expansion_utils.c
int						find_dollar(char *str);
char					*extract_var_name(char *str);
char					*build_expansion(t_expansion *exp);
char					*clean_and_strip_token(char *token);
void					free_exp(t_expansion *exp);

// expand_tokens.c
void					expand_tokens(t_token *tokens, t_env *env_copy);

// expension_preparation.c
char					*expand_variables(char *str, t_env *env_copy);
t_expansion				prepare_expansion(char *token, t_env *env_copy);

// expansion_extract.c
bool					extract_before_and_var(char *token, t_expansion *exp);
bool					extract_var_value(t_expansion *exp, t_env *env_copy);
bool					extract_after(char *token, t_expansion *exp,
							t_env *env_copy);

/* ========== SIGNALS ========== */

// signals_prompt.c
extern int				g_status;
void					handle_signal_prompt(int sig);
void					handle_child_status(int status);
void					init_signals_prompt(void);

// signals_heredoc.c
void					handle_signal_heredoc(int sig);
void					init_signals_heredoc(void);
void					reset_signals_to_default(void);

// execute_cmd.c
int						execute_cmd(t_export *export, t_command *commands,
							t_pipex *pipex);
char					**env_list_to_tab(t_env *env);

// execute_utils.c
int						env_list_size(t_env *env);
void					free_tab(char **tab);
void					free_execute(t_export *export, t_pipex *pipex);

// pipe_handle.c
int						child_process(t_command *command, t_pipex *pipex,
							t_export *export);
int						fork_and_exec(t_pipex *pipex, t_command *command,
							t_export *export);

// redirection.c
int						redirection(t_pipex *pipex, t_command *command,
							t_export *export);

// pipe_utils.c
void					safe_close(int *fd);
int						restore_prompt(t_pipex *pipex);
int						is_pipeline(t_command *commands, t_pipex *pipex,
							t_export *export);
int						check_pipe(t_pipex *pipex, t_command *command,
							t_export *export);
char					*find_token(t_token *token_list, t_token_type type);

// open_files.c
void					open_heredoc(t_command *command);

// builtin_utils.c
void					sort_env_tab(char **env_tab);

// builtin.c
int						execute_builtin(t_command *command, t_export *export,
							t_pipex *pipex);
int						is_builtin(t_command *commands);

// builtin_export.c
void					new_export(t_export *export, t_command *command);
int						builtin_export(t_export *export, t_command *command);

// builtin_echo.c
int						builtin_echo(char **args, t_pipex *pipex);

// builtin_env.c
int						builtin_env(t_env *env);

// builtin_pwd.c
int						builtin_pwd(void);

// builtin_unset.c
int						builtin_unset(t_export *export, t_command *command);

// builtin_cd.c
int						builtin_cd(t_command *command, t_env **env);

// builtin_exit.c
int						builtin_exit(t_command *command, t_export *export,
							t_pipex *pipex);

// env_handle.c
char					*my_getenv(t_env *env, char *var);
void					my_setenv(t_env **env, char *var, char *content);

/* ========== COLORS ========== */

// prompt
# define RESET "\001\033[0m\002"
# define PINK "\001\033[1;38;2;255;20;147m\002"

#endif
