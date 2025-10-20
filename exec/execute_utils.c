/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:40:48 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/20 18:03:32 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dash_before_equal(char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' || !ft_isalpha(arg[i]))
			break ;
		i++;
	}
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '=')
			break ;
		j++;
	}
	if (i < j)
		return (1);
	return (0);
}

char	*join_path_cmd(char *dir, char *cmd)
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

int	env_list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	free_tab(char **tab)
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

void	free_execute(t_export *export, t_pipex *pipex)
{
	free_env_chained(export->env);
	free_env_chained(export->export);
	free(export);
	free_commands(pipex->commands_head);
	free(pipex);
	rl_clear_history();
}
