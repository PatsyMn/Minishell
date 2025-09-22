/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:57:35 by mbores            #+#    #+#             */
/*   Updated: 2025/09/22 17:38:53 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_echo(t_command *command)
{
    int i;
    int n;
    int printable;

    i = 1;
    n = 0;
    printable = 0;
    while (command->args[i])
    {
        if (!ft_strncmp(command->args[i], "-n", 2) && !printable)
            n++;
        else
        {
            printf("%s", command->args[i]);
            if (command->args[i + 1])
                printf(" ");
            printable++;
        }
        i++;
    }
    if (!n)
        printf("\n");
    return (1);
}

int builtin_env(char **env)
{
    int i;
    
    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (1);
}
