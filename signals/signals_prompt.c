/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:53:11 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/14 21:27:26 by pmeimoun         ###   ########.fr       */
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

void	handle_child_status(int exit_status)
{
	int	signal;

	if (WIFEXITED(exit_status))
		g_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		signal = WTERMSIG(exit_status);
		g_status = 128 + signal;
		if (signal == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		else if (signal == SIGINT)
			write(1, "\n", 1);
	}
}

void	init_signals_prompt(void)
{
	signal(SIGINT, handle_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
}
