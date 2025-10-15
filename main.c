/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:30:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/15 12:37:52 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_in_main(t_shell *shell)
{
	free_env_chained(shell->export->env);
	free_env_chained(shell->export->export);
	free(shell->export);
	rl_clear_history();
}

int	init_pipex(t_pipex *pipex, t_command *commands)
{
	pipex->n = 0;
	pipex->commands_head = commands;
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.export = malloc(sizeof(t_export));
	if (!shell.export)
		return (1);
	shell.ret = 1;
	shell.prompt = PINK "WhatTheShell" RESET "$ \001\002";
	shell.export->env = copy_env_chained(envp);
	shell.export->export = copy_env_chained(envp);
	g_status = 0;
	while (shell.ret)
	{
		init_signals_prompt();
		shell.input = readline(shell.prompt);
		if (!shell.input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		shell.ret = handle_input(shell.input, shell.export);
	}
	free_in_main(&shell);
	return (g_status);
}
