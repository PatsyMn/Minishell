/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:48:32 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/18 13:57:36 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_expansion(t_expansion *exp)
{
	if (!exp)
		return;
	exp->before = NULL;
	exp->var_name = NULL;
	exp->after = NULL;
	exp->result = NULL;
	exp->var_value = NULL;
	exp->dollar_pos = -1;
}

// void	init_split_state(t_split_state *state)
// {
// 	state->result =	NULL;
// 	state->input = 	NULL;
// 	state->context = NULL;
// 	state->start = NULL;
// 	state->i= 0;
// }

// void	init_command(t_command *command)
// {

// }
