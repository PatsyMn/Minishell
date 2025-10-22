/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:02:26 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/22 18:37:52 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal_heredoc(int signal)
{
	int	dev_null;

	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 99;
		dev_null = open("/dev/null", O_RDONLY);
		if (dev_null != -1)
		{
			dup2(dev_null, STDIN_FILENO);
			close(dev_null);
		}
	}
	// if (signal == SIGQUIT)
	// 	printf("\e2D  \e2D");
}

void	init_signals_heredoc(void)
{
	signal(SIGINT, handle_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
