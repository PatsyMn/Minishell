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

int execute_cmd(char **envp, t_token *token_list, t_command *commands)
{
    char	**argv_exec;

    open_file(commands);
    if (dup2(commands->infile_fd, STDIN_FILENO) == -1
        || dup2(commands->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 error");
		return (0);
	}
    argv_exec = malloc(sizeof(char *) * 4);
    if (!argv_exec)
	{
		perror("malloc error");
		return (0);
	}
    argv_exec[0] = "/bin/sh";
	argv_exec[1] = "-c";
	argv_exec[2] = ;
	argv_exec[3] = NULL;
	execve("/bin/sh", argv_exec, var.envp);
	perror("execve failed");
	free(argv_exec);
    return (0);
}
