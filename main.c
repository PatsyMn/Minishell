/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/25 11:49:50 by mbores           ###   ########.fr       */
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

static int	handle_tokens(char **split_input, t_export *export)
{
	t_token		*token_list;
	t_command	*commands;
	// t_pipex		*pipex;
	// int			status;

	// pipex = malloc(sizeof(t_pipex));
	token_list = tokenizer(split_input, export->env);
	free_split(split_input);
	if (token_list)
	{
		assign_filename_types(token_list);
		expand_tokens(token_list, export->env);
		commands = parser(token_list);
		if (!ft_strncmp(commands->args[0], "unset", 5))
			builtin_unset(export, commands);
		else if (!ft_strncmp(commands->args[0], "env", 3))
			builtin_env(export->env);
		else if (!ft_strncmp(commands->args[0], "export", 6))
			builtin_export(export, commands);
		// child_process(commands, pipex, env_copy);
		// while (wait(&status) > 0)
		// 	;
		// child_signal(status);
		// free(pipex);
		free_commands(commands);
		free_tokens(token_list);
	}
	return (1);
}

static int	handle_input(char *input, t_export	*export)
{
	char	**split_input;

	if (!input)
		return (0);
	if (check_unclosed_quotes(input) || check_special_chars(input))
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

	(void)ac;
	(void)av;
	export = malloc(sizeof(t_export));
	if (!export)
		return (1);
	export->env = copy_env_chained(envp);
	export->export = copy_env_chained(envp);
	if (!export->env || !export->export)
		return (1);
	ret = 1;
	while (ret)
	{
		input = readline("WhatTheShell$ ");
		ret = handle_input(input, export);
	}
	free_env_chained(export->env);
	free_env_chained(export->export);
	free(export);
	return (0);
}

