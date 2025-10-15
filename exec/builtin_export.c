/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:24:58 by mbores            #+#    #+#             */
/*   Updated: 2025/10/15 14:47:36 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_key_value(char **key_value)
{
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
}

static int	add_export(t_export *export, t_command *command, int i)
{
	char	*equal;
	char	**key_value;

	equal = ft_strchr(command->args[i], '=');
	if (equal)
	{
		if (command->args[i][ft_strlen(equal) - 1] != '+')
		{
			key_value = ft_split(command->args[i], '=');
			my_setenv(&export->export, ft_strdup(key_value[0]),
				ft_strdup(key_value[1]));
			my_setenv(&export->env, ft_strdup(key_value[0]),
				ft_strdup(key_value[1]));
			free_key_value(key_value);
			return (1);
		}
	}
	return (0);
}

static int	append_export(t_export *export, t_command *command, int i)
{
	char	*plus;
	char	**key_value;
	char	*env;

	plus = ft_strchr(command->args[i], '+');
	if (plus)
	{
		if (plus[1] == '=')
		{
			key_value = new_ft_split(command->args[i], "+=");
			env = my_getenv(export->export, key_value[0]);
			if (!env)
				env = key_value[1];
			else
				ft_strlcat(env, key_value[1],
					ft_strlen(env) + ft_strlen(key_value[1]) + 1);
			my_setenv(&export->export, ft_strdup(key_value[0]), ft_strdup(env));
			my_setenv(&export->env, ft_strdup(key_value[0]), ft_strdup(env));
			free_key_value(key_value);
			return (1);
		}
	}
	return (0);
}

static void	new_export(t_export *export, t_command *command)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (command->args[i])
	{
		while (command->args[i][j])
		{
			if (command->args[i][j] == '+' && command->args[i][j + 1] != '=')
			{
				perror("WhatTheShell: export");
				return ;
			}
			else if (append_export(export, command, i))
				break ;
			else if (add_export(export, command, i))
				break ;
			else if (!command->args[i][j + 1])
				my_setenv(&export->export, ft_strdup(command->args[i]), NULL);
			j++;
		}
		j = 0;
		i++;
	}
}

int	builtin_export(t_export *export, t_command *command)
{
	char	**export_tab;
	char	*equal;
	int		i;

	if (command->args[1])
	{
		new_export(export, command);
		return (0);
	}
	export_tab = env_list_to_tab(export->export);
	sort_env_tab(export_tab);
	i = 0;
	while (export_tab[i])
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
