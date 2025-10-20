/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:58:36 by mbores            #+#    #+#             */
/*   Updated: 2025/10/20 14:40:26 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_home(t_env **env, char *oldpwd)
{
	char	*home;

	if (!env || !*env)
	{
		write(2, "WhatTheShell: cd: HOME not set\n", 31);
		free(oldpwd);
		return (1);
	}
	home = my_getenv(*env, "HOME");
	if (!home)
	{
		write(2, "WhatTheShell: cd: HOME not set\n", 31);
		free(oldpwd);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("WhatTheShell: cd");
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_command *command, t_env **env)
{
	char	*oldpwd;
	char	*newpwd;

	if (command->args[2])
	{
		write(STDERR_FILENO, "WhatTheShell: cd: too many arguments\n", 37);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!command->args[1])
	{
		if (cd_home(env, oldpwd))
			return (1);
	}
	if (!ft_strncmp(command->args[1], my_getenv(*env, "PWD"), ft_strlen(command->args[1])))
	{
		free(oldpwd);
		return (0);
	}
	if (chdir(command->args[1]) == -1)
	{
		perror("WhatTheShell: cd");
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
