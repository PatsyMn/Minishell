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

static char	*concat_command(t_command *command)
{
	char	*cmd;
	char	*tmp;
	int		i;

	cmd = NULL;
	i = 0;
	cmd = ft_strjoin(cmd, command->args[i]);
	i++;
	while (command->args[i])
	{
		if (command->outfile && !ft_strncmp(command->outfile, command->args[i], ft_strlen(command->outfile)))
			break ;
		tmp = ft_strjoin(cmd, " ");
		free(cmd);
		cmd = tmp;
		tmp = ft_strjoin(cmd, command->args[i]);
		free(cmd);
		cmd = tmp;
		i++;
	}
	return (cmd);
}

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
    char	**argv_exec;
	char	**env_tab;
	char	*cmd;

	cmd = concat_command(commands);
	env_tab = env_list_to_tab(envp);
    argv_exec = malloc(sizeof(char *) * 4);
    if (!argv_exec)
	{
		perror("malloc error");
		exit(1);
	}
    argv_exec[0] = "/bin/sh";
	argv_exec[1] = "-c";
	argv_exec[2] = cmd;
	argv_exec[3] = NULL;
	setup_signals_exec();
	execve("/bin/sh", argv_exec, env_tab);
	perror("execve failed");
	free(argv_exec);
    exit(1);
}
