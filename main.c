/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/27 16:50:27 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	char		**env_copy;
	char		**split_input;
	t_token		*token_list;
	t_command	*commands;

	(void)ac;
	(void)av;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	while (1)
	{
		input = readline("WhatTheShell$ ");
		if (!input)
			break ;
		if (!check_unclosed_quotes(input) && !check_special_chars(input))
		{
			split_input = split_input_respecting_quotes(input);
			if (split_input)
			{
				token_list = tokenizer(split_input);
				expand_tokens(token_list, env_copy);
				print_tokens(token_list);
				commands = parser(token_list);
				print_commands(commands);
				free_commands(commands);
				free_tokens(token_list);
				free_split(split_input);
			}
		}
		free(input);
	}
	free_env(env_copy);
	return (0);
}
