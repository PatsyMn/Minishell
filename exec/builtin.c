/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:24:44 by mbores            #+#    #+#             */
/*   Updated: 2025/10/03 14:26:15 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int execute_builtin_2(t_command_2 *commands, t_export *export)
{
    if (!ft_strncmp(commands->args_list[0], "export", 7))
        return (builtin_export(export, commands));
    else if (!ft_strncmp(commands->args_list[0], "unset", 6))
        return (builtin_unset(export, commands));
    else if (!ft_strncmp(commands->args_list[0], "cd", 3))
        return (builtin_cd(commands, &export->env));
    else if (!ft_strncmp(commands->args_list[0], "exit", 5))
        return (builtin_exit(commands));
    return (-1);
}

int execute_builtin(t_command_2 *commands, t_export *export)
{
    if (!commands->args_list || !commands->args_list[0])
        return (-1);
    else if (!ft_strncmp(commands->args_list[0], "echo", 5))
        return (builtin_echo(commands->args_list));
    else if (!ft_strncmp(commands->args_list[0], "env", 4) && !commands->args_list[1])
        return (builtin_env(export->env));
    else if (!ft_strncmp(commands->args_list[0], "pwd", 4) && !commands->args_list[1])
        return (builtin_pwd(export->env));
    else
        return (execute_builtin_2(commands, export));
}
