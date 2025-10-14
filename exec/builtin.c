/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:24:44 by mbores            #+#    #+#             */
/*   Updated: 2025/10/14 14:24:14 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_builtin_2(t_command *commands, t_export *export,
		t_pipex *pipex)
{
	if (!ft_strncmp(commands->args[0], "export", 7))
		return (builtin_export(export, commands));
	else if (!ft_strncmp(commands->args[0], "unset", 6))
		return (builtin_unset(export, commands));
	else if (!ft_strncmp(commands->args[0], "cd", 3))
		return (builtin_cd(commands, &export->env));
	else if (!ft_strncmp(commands->args[0], "exit", 5))
		return (builtin_exit(commands, export, pipex));
	return (-1);
}

int	execute_builtin(t_command *commands, t_export *export, t_pipex *pipex)
{
	if (!commands->args)
		return (0);
	else if (!ft_strncmp(commands->args[0], "echo", 5))
		return (builtin_echo(commands->args, pipex));
	else if (!ft_strncmp(commands->args[0], "env", 4) && !commands->args[1])
		return (builtin_env(export->env));
	else if (!ft_strncmp(commands->args[0], "pwd", 4) && !commands->args[1])
		return (builtin_pwd());
	else
		return (execute_builtin_2(commands, export, pipex));
}

int	is_builtin(t_command *commands)
{
	if (!commands->args)
		return (1);
	if (!ft_strncmp(commands->args[0], "echo", 5)
		|| (!ft_strncmp(commands->args[0], "env", 4) && !commands->args[1])
		|| (!ft_strncmp(commands->args[0], "pwd", 4) && !commands->args[1])
		|| !ft_strncmp(commands->args[0], "export", 7)
		|| !ft_strncmp(commands->args[0], "unset", 6)
		|| !ft_strncmp(commands->args[0], "cd", 3)
		|| !ft_strncmp(commands->args[0], "exit", 5))
		return (1);
	return (0);
}
