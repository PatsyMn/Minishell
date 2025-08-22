/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 15:49:15 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *input;

	while (1)
	{
		input = readline("WhatTheShell$ ");
		if (!input)
		{
			printf("exit\n");
			return (0);
		}
		if (check_unclosed_quotes(input))
		{
			printf("Error: invalid special characters detected\n");
			free(input);
		}
		if (check_special_chars(input))
		{
			printf("Error: 2");
			free(input);
		}
		char **split_input = split_input_respecting_quotes(input);
		if (split_input)
		{
			t_token *token_list = tokenizer(split_input);
			print_tokens(token_list);
			t_command *commands = parser(token_list);
			print_commands(commands);
			if (!token_list)
			{
				printf("Error: 4");
				free_split(split_input);
				free(input);
				free_tokens(token_list);
			}
		}
		free_split(split_input);
		free(input);
	}
	return (0);
}

