/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/11 13:08:09 by mbores            #+#    #+#             */
/*   Updated: 2025/09/11 13:08:09 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static void	check_file(char *cmd, char **env, t_export *export, t_pipex *pipex)
{
	struct stat	st;

	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, "WhatTheShell: ", 14);
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			free(cmd);
			free_tab(env);
			free_execute(export, pipex);
			exit(126);
		}
	}
}

static char	*find_cmd(char *cmd, t_env *env)
{
	char	**path;
	char	*path_cmd;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = ft_split(my_getenv(env, "PATH"), ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path_cmd = join_path_cmd(path[i], cmd);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	free_tab(path);
	return (NULL);
}

char	**env_list_to_tab(t_env *env)
{
	char	**env_tab;
	char	*line;
	int		i;

	i = env_list_size(env);
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->content)
		{
			line = ft_strjoin(env->key, "=");
			env_tab[i] = ft_strjoin(line, env->content);
			free(line);
		}
		else
			env_tab[i] = ft_strdup(env->key);
		env = env->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

int	execute_cmd(t_export *export, t_command *commands, t_pipex *pipex)
{
	char	**env_tab;
	char	*cmd;

	env_tab = env_list_to_tab(export->env);
	cmd = find_cmd(commands->args[0], export->env);
	if (!cmd)
	{
		write(STDERR_FILENO, "WhatTheShell: ", 14);
		write(STDERR_FILENO, commands->args[0], ft_strlen(commands->args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		free_tab(env_tab);
		free_execute(export, pipex);
		exit(127);
	}
	check_file(cmd, env_tab, export, pipex);
	reset_signals_to_default();
	execve(cmd, commands->args, env_tab);
	perror("WhatTheShell");
	free(cmd);
	free_tab(env_tab);
	free_execute(export, pipex);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}
