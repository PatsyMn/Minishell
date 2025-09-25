/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:21 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 16:39:59 by mbores           ###   ########.fr       */
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
            n = 1;
        else
        {
            printf("%s", command->args[i]);
            if (command->args[i + 1])
                printf(" ");
            printable = 1;
        }
        i++;
    }
    if (!n)
        printf("\n");
    return (0);
}
