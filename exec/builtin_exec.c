/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:57:35 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 11:56:53 by mbores           ###   ########.fr       */
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
        if (!printable && ft_strncmp(command->args[i], "-n", 2))
            return (0);
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

int builtin_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->content);
        env = env->next;
    }
    return (1);
}

int builtin_pwd(t_env *env)
{
    while (env)
    {
        if (!ft_strncmp(env->key, "PWD", 3) && env->key[3] == '\0')
            printf("%s\n", env->content);
        env = env->next;
    }
    return (1);
}

int builtin_export(t_export *export, t_command *command)
{
    char    **export_tab;
    char    *equal;
    int     i;

    if (command->args[1])
    {
        new_export(export, command);
        return (1);
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
    return (1);
}
