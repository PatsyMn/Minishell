/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:24:58 by mbores            #+#    #+#             */
/*   Updated: 2025/10/09 17:10:22 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    new_export(t_export *export, t_command *command)
{
    char    *equal;
    size_t  len;
    int     i;

    i = 0;
    while (command->args[i])
    {
        equal = ft_strchr(command->args[i], '=');
        if (equal)
        {
            len = equal - command->args[i];
            my_setenv(&export->export,
                ft_substr(command->args[i], 0, len),
                ft_strdup(equal + 1));
            my_setenv(&export->env,
                ft_substr(command->args[i], 0, len),
                ft_strdup(equal + 1));
            i++;
            continue ;
        }
        my_setenv(&export->export, command->args[1], NULL);
        i++;
    }
}

int builtin_export(t_export *export, t_command *command)
{
    char    **export_tab;
    char    *equal;
    int     i;

    if (command->args[1])
    {
        new_export(export, command);
        return (0);
    }
    export_tab = env_list_to_tab(export->export);
    sort_env_tab(export_tab);
    i = 0;
    while(export_tab[i])
    {
        equal = ft_strchr(export_tab[i], '=');
        if (equal)
            printf("declare -x %.*s=\"%s\"\n", (int)(equal - export_tab[i]),
                export_tab[i], equal + 1);
        else
            printf("declare -x %s\n", export_tab[i]);
        i++;
    }
    free_env(export_tab);
    return (0);
}
