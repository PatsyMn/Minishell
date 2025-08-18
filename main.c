/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/18 15:17:25 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	char *input = av[1];
	if (check_unclosed_quotes(input))
		return (1);
	if (check_special_chars(input))
		return (1);
	char **split_input = split_input_respecting_quotes(input);
	if (!split_input)
		return (1);
	t_token *token_list = tokenizer(split_input);
	free_split(split_input);
	return (0);
}
