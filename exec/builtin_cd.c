/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:58:36 by mbores            #+#    #+#             */
/*   Updated: 2025/10/20 17:55:32 by mbores           ###   ########.fr       */
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

static int	update_pwd_vars(t_env **env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
		my_setenv(env, "OLDPWD", oldpwd);
	my_setenv(env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	builtin_cd(t_command *command, t_env **env)
{
	char	*oldpwd;
	char	*pwd;

	if (command->args[2])
		return (write(2, "WhatTheShell: cd: too many arguments\n", 37), 1);
	oldpwd = getcwd(NULL, 0);
	if (!command->args[1])
		return (cd_home(env, oldpwd));
	pwd = my_getenv(*env, "PWD");
	if (pwd && !ft_strncmp(command->args[1], pwd, ft_strlen(command->args[1])))
		return (free(oldpwd), 0);
	if (chdir(command->args[1]) == -1)
	{
		perror("WhatTheShell: cd");
		free(oldpwd);
		return (1);
	}
	return (update_pwd_vars(env, oldpwd));
}
