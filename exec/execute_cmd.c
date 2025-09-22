/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:08:09 by mbores            #+#    #+#             */
/*   Updated: 2025/09/11 13:08:09 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*concat(t_command *command)
{
	char	*cmd;
	char	*tmp;
	int		i;

	cmd = NULL;
	i = 0;
	cmd = ft_strjoin(cmd, command->args[i]);
	i++;
	while (command->args[i])
	{
		if (command->outfile && !ft_strncmp(command->outfile, command->args[i], ft_strlen(command->outfile)))
			break ;
		tmp = ft_strjoin(cmd, " ");
		free(cmd);
		cmd = tmp;
		tmp = ft_strjoin(cmd, command->args[i]);
		free(cmd);
		cmd = tmp;
		i++;
	}
	return (cmd);
}

int	dup2_error(t_command *command, t_pipex *pipex, int fd_out)
{
	if ((command->infile && !pipex->cmd_count) || pipex->cmd_count)
	{
		if (dup2(pipex->input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 error");
			return (0);
		}
	}
	if (command->outfile && !command->next)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			return (0);
		}
	}
	return (1);
}

int execute_cmd(char **envp, t_command *commands, t_pipex *pipex, int fd_out)
{
    char	**argv_exec;
	char	*cmd;

	cmd = concat(commands);
    if (!dup2_error(commands, pipex, fd_out))
		exit(1);
    argv_exec = malloc(sizeof(char *) * 4);
    if (!argv_exec)
	{
		perror("malloc error");
		exit(1);
	}
    argv_exec[0] = "/bin/sh";
	argv_exec[1] = "-c";
	argv_exec[2] = cmd;
	argv_exec[3] = NULL;
	execve("/bin/sh", argv_exec, envp);
	perror("execve failed");
	free(argv_exec);
    exit(1);
}
