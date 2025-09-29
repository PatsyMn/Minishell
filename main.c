/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/29 12:56:41 by pmeimoun         ###   ########.fr       */
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

static int	handle_tokens(char **split_input, char **env_copy)
{
	t_token		*token_list;
	t_command	*commands;
	t_pipex		*pipex;
	int			status;

	pipex = malloc(sizeof(t_pipex));
	token_list = tokenizer(split_input, env_copy);
	free_split(split_input);
	if (token_list)
	{
		assign_filename_types(token_list);
		expand_tokens(token_list, env_copy);
		commands = parser(token_list);
		child_process(commands, pipex, env_copy);
		while (wait(&status) > 0)
			;
		free(pipex);
		free_commands(commands);
		free_tokens(token_list);
	}
	return (1);
}

static int	handle_input(char *input, char **env_copy)
{
	char	**split_input;

	if (!input)
		return (0);
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
	return (handle_tokens(split_input, env_copy));
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	char		**env_copy;
	int			ret;
	const char	*prompt;

	(void)ac;
	(void)av;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	prompt = PINK "WhatTheShell" RESET "$ ";
	ret = 1;
	while (ret)
	{
		input = readline(prompt);
		ret = handle_input(input, env_copy);
	}
	free_env(env_copy);
	return (0);
}

