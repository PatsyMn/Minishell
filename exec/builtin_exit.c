/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:49:08 by mbores            #+#    #+#             */
/*   Updated: 2025/09/30 13:01:00 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_numeric(const char *str)
{
    if (!str || !*str)
        return 0;
    if (*str == '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int builtin_exit(t_command *command)
{
    int exit_code;

    exit_code = g_status;
    write(1, "exit\n", 5);
    if (command->args[1])
    {
        if (!is_numeric(command->args[1]))
        {
            write(2, "exit: numeric argument required\n", 31);
            exit(255);
        }
        exit_code = ft_atoi(command->args[1]);
        if (command->args[2])
        {
            write(2, "exit: too many arguments\n", 25);
            return (1);
        }
    }
    exit(exit_code);
}
