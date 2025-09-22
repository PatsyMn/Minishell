/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:24:44 by mbores            #+#    #+#             */
/*   Updated: 2025/09/22 16:59:46 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cd, exit, export, unset, echo, env, pwd

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (!ft_strncmp(cmd, "cd", 2) ||
        !ft_strncmp(cmd, "exit", 4) ||
        !ft_strncmp(cmd, "export", 6) ||
        !ft_strncmp(cmd, "unset", 5) ||
        !ft_strncmp(cmd, "echo", 4) ||
        !ft_strncmp(cmd, "env", 3) ||
        !ft_strncmp(cmd, "pwd", 3))
        return (1);
    return (0);
}

int    execute_builtin(t_command *command, char **env)
{
    if (!command->args || !command->args[0])
        return (1);
    if (strcmp(command->args[0], "echo") == 0)
        return (builtin_echo(command->args));
    if (strcmp(command->args[0], "cd") == 0)
        return (builtin_cd(command->args, env));
    if (strcmp(command->args[0], "exit") == 0)
        return (builtin_exit(command->args));
    if (strcmp(command->args[0], "export") == 0)
        return (builtin_export(command->args, env));
    if (strcmp(command->args[0], "unset") == 0)
        return (builtin_unset(command->args, env));
    if (strcmp(command->args[0], "pwd") == 0)
        return (builtin_pwd());
    if (strcmp(command->args[0], "env") == 0)
        return (builtin_env(env));
    return (1);
}
