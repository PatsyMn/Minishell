/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 18:15:08 by pmeimoun         ###   ########.fr       */
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
			return (0);
		}
		if (check_unclosed_quotes(input))
		{
			free(input);
			return (0);
		}
		if (check_special_chars(input))
		{
			free(input);
			return (0);
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

