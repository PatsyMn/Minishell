/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:51:02 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 17:41:10 by pmeimoun         ###   ########.fr       */
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

static int	execute_pipeline(t_command *commands, t_export *export)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex || !init_pipex(pipex, commands))
	{
		free(pipex);
		free_commands(commands);
		return (0);
	}
	child_process(commands, pipex, export);
	wait_child();
	unlink("temp");
	free(pipex);
	free_commands(commands);
	return (1);
}

static int	handle_tokens(char **split_input, t_export *export)
{
	t_token		*token_list;
	t_command	*commands;

	token_list = tokenizer(split_input, export->env);
	print_token_list(token_list);
	if (!token_list)
		return (0);
	assign_filename_types(token_list);
	if (!expand_tokens(token_list, export->env))
	{
		free_tokens(token_list);
		return (0);
	}
	commands = parser(token_list);
	// print_token_list(commands->token_list);
	free_tokens(token_list);
	if (!commands)
		return (0);
	return (execute_pipeline(commands, export));
}

int	handle_input(char *input, t_export *export)
{
	char	**split_input;
	int		ret;

	if (ft_strlen(input) == 0)
	{
		free(input);
		return (1);
	}
	add_history(input);
	if (check_unclosed_quotes(input))
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
	ret = handle_tokens(split_input, export);
	free_split(split_input);
	if (!ret)
		return (1);
	return (1);
}
