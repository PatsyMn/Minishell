/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/08 13:02:29 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_syntax_errors(char **split_input)
{
	if (has_syntax_error_first_pipe(split_input)
		|| check_syntax_operators(split_input)
		|| has_syntax_error_last_pipe(split_input)
		|| has_syntax_error_ampersand(split_input))
	{
		free_split(split_input);
		return (1);
	}
	return (0);
}

void	wait_child()
{
	int wstatus;
	
	while (wait(&wstatus) > 0)
		handle_child_status(wstatus);
}

static int	handle_tokens(char **split_input, t_export *export)
{
	t_token		*token_list;
	t_command	*commands;
	t_pipex		*pipex;

	token_list = tokenizer(split_input, export->env);
	free_split(split_input);
	if (token_list)
	{
		pipex = malloc(sizeof(t_pipex));
		if (!pipex)
			return (0);
		assign_filename_types(token_list);
		expand_tokens(token_list, export->env);
		commands = parser(token_list);
		// print_tokens(token_list);
		child_process(commands, pipex, export);
		wait_child();
		// print_commands(commands);
		free(pipex);
		free_tokens(token_list);
		free_commands(commands);
	}
	return (1);
}

static int	handle_input(char *input, t_export	*export)
{
	char	**split_input;

	if (ft_strlen(input) == 0)
	{
		free(input);
		return (1);
	}
	add_history(input);
	if (check_unclosed_quotes(input)) /*|| check_special_chars(input))*/
	{
		free(input);
		return (1);
	}
	split_input = split_input_respecting_quotes(input);
	free(input);
	if (!split_input)
		return (1);
	if (handle_syntax_errors(split_input))
		return (1);
	return (handle_tokens(split_input, export));
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_export	*export;
	int			ret;
	const char	*prompt;

	(void)ac;
	(void)av;
	export = malloc(sizeof(t_export));
	if (!export)
		return (1);
	ret = 1;
	prompt = PINK "WhatTheShell" RESET "$ ";
	export->env = copy_env_chained(envp);
	export->export = copy_env_chained(envp);
	g_status = 0;
	while (ret)
	{
		init_signals_prompt();
		input = readline(prompt);
		if (!input)
			break ;
		ret = handle_input(input, export);
	}
	free_env_chained(export->env);
	free_env_chained(export->export);
	free(export);
	rl_clear_history();
	return (0);
}

