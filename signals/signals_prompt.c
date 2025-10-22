/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:53:11 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/22 18:27:38 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_status = 0;

void	handle_signal_prompt(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	wait_child(void)
{
	int	children;
	int	wstatus;
	int	signum;

	children = 0;
	while (wait(&wstatus) > 0)
		++children;
	if (!children)
		return ;
	if ((wstatus & 0x7F) == 0)
		g_status = (wstatus >> 8) & 0xFF;
	else
	{
		signum = wstatus & 0x7F;
		g_status = 128 + signum;
		if (signum == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		else if (signum == SIGINT)
			write(1, "\n", 1);
	}
}

void	init_signals_prompt(void)
{
	signal(SIGINT, handle_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
}
