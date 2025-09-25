/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:11:36 by mbores            #+#    #+#             */
/*   Updated: 2025/09/24 16:01:03 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    sort_env_tab(char **env_tab)
{
    int   i;
    int   j;
    char  *tmp;

    for (i = 0; env_tab[i]; i++)
    {
        for (j = i + 1; env_tab[j]; j++)
        {
            if (ft_strncmp(env_tab[i], env_tab[j], ft_strlen(env_tab[i])) > 0)
            {
                tmp = env_tab[i];
                env_tab[i] = env_tab[j];
                env_tab[j] = tmp;
            }
        }
    }
}

void    new_export(t_export *export, t_command *command)
{
    char    *equal;
    size_t  len;

    equal = ft_strchr(command->args[1], '=');
    if (equal)
    {
        len = equal - command->args[1];
        my_setenv(&export->export,
            ft_substr(command->args[1], 0, len),
            ft_strdup(equal + 1));
        my_setenv(&export->env,
            ft_substr(command->args[1], 0, len),
            ft_strdup(equal + 1));
        return ;
    }
    my_setenv(&export->export, command->args[1], NULL);
}
