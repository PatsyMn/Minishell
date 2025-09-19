/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:48:32 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/19 16:01:49 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_expansion(t_expansion *exp)
{
	if (!exp)
		return ;
	exp->before = NULL;
	exp->var_name = NULL;
	exp->after = NULL;
	exp->result = NULL;
	exp->var_value = NULL;
	exp->dollar_pos = -1;
}
