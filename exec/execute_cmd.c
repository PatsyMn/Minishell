/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:08:09 by mbores            #+#    #+#             */
/*   Updated: 2025/09/11 13:08:09 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	*concat_command(t_command *command)
// {
// 	char	*cmd;
// 	char	*tmp;
// 	int		i;

// 	if (!command->args || !command->args[0])
// 		return (NULL);
// 	cmd = NULL;
// 	i = 0;
// 	cmd = ft_strjoin(cmd, command->args[i]);
// 	i++;
// 	while (command->args[i])
// 	{
// 		if (command->outfile && !ft_strncmp(command->outfile, command->args[i], ft_strlen(command->outfile)))
// 			break ;
// 		tmp = ft_strjoin(cmd, " ");
// 		free(cmd);
// 		cmd = tmp;
// 		tmp = ft_strjoin(cmd, command->args[i]);
// 		free(cmd);
// 		cmd = tmp;
// 		i++;
// 	}
// 	return (cmd);
// }

static int env_list_size(t_env *env)
{
    int i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return (i);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

static char	*find_cmd(char *cmd, t_env *env)
{
	char	**path;
	char	*path_cmd;
	int		i;

	path = ft_split(my_getenv(env, "PATH"), ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(path_cmd, cmd);
		if (access(path_cmd, X_OK) == 0)
		{
			free_tab(path);
			return (path_cmd);
		}
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

int execute_cmd(t_env *envp, t_command *commands)
{
	char	**env_tab;
	char	*cmd;

	env_tab = env_list_to_tab(envp);
	cmd = find_cmd(commands->args[0], envp);
	if (!cmd)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, commands->args[0], ft_strlen(commands->args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		free_tab(env_tab);
		exit(127);
	}
	setup_signals_exec();
	execve(cmd, commands->args, env_tab);
	perror("execve failed");
	free(cmd);
	free_tab(env_tab);
	exit(0);
}
