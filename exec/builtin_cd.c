/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:58:36 by mbores            #+#    #+#             */
/*   Updated: 2025/09/30 16:18:29 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int cd_home(t_env **env, char *oldpwd)
{
    char    *home;

    home = my_getenv(*env, "HOME");
    if (!home)
    {
        write(2, "bash: cd: HOME not set\n", 22);
        free(oldpwd);
        return (1);
    }
    else if (chdir(home) == -1)
    {
        perror("bash: cd");
        free(oldpwd);
        return (1);
    }
    return (0);
}

int builtin_cd(t_command *command, t_env **env)
{
    char    *oldpwd;
    char    *newpwd;

    oldpwd = getcwd(NULL, 0);
    if (!command->args[1])
    {
        if (cd_home(env, oldpwd))
            return (1);
    }
    else if (chdir(command->args[1]) == -1)
    {
        perror("bash: cd");
        free(oldpwd);
        return (1);
    }
    newpwd = getcwd(NULL, 0);
    if (oldpwd)
        my_setenv(env, "OLDPWD", oldpwd);
    if (newpwd)
        my_setenv(env, "PWD", newpwd);
    free(oldpwd);
    free(newpwd);
    return (0);
}
