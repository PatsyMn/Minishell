/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:46:00 by mbores            #+#    #+#             */
/*   Updated: 2025/06/26 12:04:17 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_error(int argc, int nbr)
{
	if (argc < nbr)
	{
		write(2, "Error: not enough arguments\n", 29);
		return (1);
	}
	else
		return (0);
}

int	get_exit_status(pid_t last_pid)
{
	pid_t	waited_pid;
	int		status;
	int		exit_code;

	exit_code = EXIT_FAILURE;
	waited_pid = wait(&status);
	while (waited_pid > 0)
	{
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		waited_pid = wait(&status);
	}
	return (exit_code);
}

int	init_files(t_pipex *var, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (check_error(argc, 6))
			return (1);
		read_heredoc(argv[2]);
		var->infile = open("infile", O_RDONLY);
		var->outfile = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		var->cmd_start = 3;
		var->cmd_count = argc - 4;
	}
	else
	{
		if (check_error(argc, 5))
			return (1);
		var->infile = open(argv[1], O_RDONLY);
		var->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		var->cmd_start = 2;
		var->cmd_count = argc - 3;
	}
	if (var->infile < 0)
		perror(argv[1]);
	if (var->outfile < 0)
		perror(argv[argc - 1]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	var;
	pid_t	last_pid;

	if (argc < 5)
	{
		write(2, "Error: not enough arguments\n", 29);
		return (1);
	}
	if (init_files(&var, argc, argv))
		return (1);
	var.argv = argv;
	var.envp = envp;
	last_pid = child_process(var);
	if (last_pid > 0)
		return (get_exit_status(last_pid));
	return (EXIT_FAILURE);
}
