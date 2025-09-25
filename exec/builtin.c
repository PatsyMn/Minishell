/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:24:44 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 17:02:26 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int execute_builtin_2(t_command *command, t_export *export, int status)
{
    if (!ft_strncmp(command->args[0], "export", 7))
        return (builtin_export(export, command));
    else if (!ft_strncmp(command->args[0], "unset", 6))
        return (builtin_unset(export, command));
    else if (!ft_strncmp(command->args[0], "cd", 3))
        return (builtin_cd(command, &export->env));
    else if (!ft_strncmp(command->args[0], "exit", 5))
        return (builtin_exit(command, status));
    return (-1);
}

int execute_builtin(t_command *command, t_export *export, int status)
{
    if (!command->args || !command->args[0])
        return (1);
    else if (!ft_strncmp(command->args[0], "echo", 5))
        return (builtin_echo(command));
    else if (!ft_strncmp(command->args[0], "env", 4) && !command->args[1])
        return (builtin_env(export->env));
    else if (!ft_strncmp(command->args[0], "pwd", 4) && !command->args[1])
        return (builtin_pwd(export->env));
    else
        return (execute_builtin_2(command, export, status));
}
