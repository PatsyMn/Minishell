/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:21 by mbores            #+#    #+#             */
/*   Updated: 2025/09/26 17:22:21 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_echo(char **args)
{
    int i;
    int n;
    int printable;

    i = 1;
    n = 0;
    printable = 0;
    while (args[i])
    {
        if (ft_strncmp(args[i], "-n", 2))
            return (-1);
        if (!ft_strncmp(args[i], "-n", 2) && !printable)
            n = 1;
        else
        {
            write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
            if (args[i + 1])
                write(STDOUT_FILENO, " ", 1);
            printable = 1;
        }
        i++;
    }
    if (!n)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
