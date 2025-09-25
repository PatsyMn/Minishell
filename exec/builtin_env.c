/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:25:39 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 16:43:35 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->content);
        env = env->next;
    }
    return (0);
}
