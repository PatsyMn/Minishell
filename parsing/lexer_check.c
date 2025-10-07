/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:00:05 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 12:20:24 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_single_char(char *input)
{
	if (!input)
		return (0);
	if (input[0] && input[1] == '\0')
	{
		if (input[0] == '!')
			g_status = 1;
		else if (input[0] == '#' || input[0] == ':')
			g_status = 0;
		if (input[0] == '#' || input[0] == ':' || input[0] == '!')
			return (1);
	}
	return (0);
}
