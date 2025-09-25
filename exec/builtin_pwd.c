/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:26:21 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 16:46:02 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd(t_env *env)
{
    while (env)
    {
        if (!ft_strncmp(env->key, "PWD", 3) && env->key[3] == '\0')
            printf("%s\n", env->content);
        env = env->next;
    }
    return (0);
}
