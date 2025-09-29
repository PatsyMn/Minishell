/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:00:36 by mbores            #+#    #+#             */
/*   Updated: 2025/05/11 18:25:04 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(t_pipex var, char *cmd_str, int fd_in, int fd_out)
{
	char	**argv_exec;

	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 error");
		exit(1);
	}
	argv_exec = malloc(sizeof(char *) * 4);
	if (!argv_exec)
	{
		perror("malloc error");
		exit(1);
	}
	argv_exec[0] = "/bin/sh";
	argv_exec[1] = "-c";
	argv_exec[2] = cmd_str;
	argv_exec[3] = NULL;
	execve("/bin/sh", argv_exec, var.envp);
	perror("execve failed");
	free(argv_exec);
	exit(1);
}
