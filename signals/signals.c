/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:02:26 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/22 16:23:21 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t g_status = 0;

void	handle_signal_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(0); // ferme stdin pour casser readline dans le heredoc
		rl_on_new_line();
		g_status = 99; // 99 = code spécial pour que le shell sache qu'on a interrompu un heredoc
	}
}

void	child_signal(int status)
{
	int sig;

	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		g_status = 128 + sig;
		if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(1, "\n", 1);
	}
}
void	setup_signals_shell(void)
{
	signal(SIGINT, handle_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
}
void	setup_signals_heredoc(void)
{
	signal(SIGINT, signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
void	setup_signals_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
