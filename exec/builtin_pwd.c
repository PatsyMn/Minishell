/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:26:21 by mbores            #+#    #+#             */
/*   Updated: 2025/10/09 13:52:33 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd()
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        write(STDOUT_FILENO, pwd, ft_strlen(pwd));
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}
