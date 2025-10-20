/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:24:58 by mbores            #+#    #+#             */
/*   Updated: 2025/10/20 18:03:02 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_export(t_export *export, t_command *command, int i)
{
	char	*equal;
	char	**key_value;
	char	*key;
	char	*value;

	equal = ft_strchr(command->args[i], '=');
	if (!equal)
		return (0);
	key_value = ft_split(command->args[i], '=');
	if (!key_value || !key_value[0])
		return (0);
	key = ft_strdup(key_value[0]);
	value = NULL;
	if (key_value[1])
		value = ft_strdup(key_value[1]);
	add_to_envs(export, key, value);
	free_key_value(key_value);
	free(key);
	free(value);
	return (1);
}

static int	append_export(t_export *export, t_command *command, int i)
{
	char	**key_value;

	if (!ft_strnstr(command->args[i], "+=", ft_strlen(command->args[i])))
		return (0);
	key_value = new_ft_split(command->args[i], "+=");
	if (!key_value || !key_value[0])
	{
		free_key_value(key_value);
		return (0);
	}
	append_to_envs(&export->export, key_value[0], key_value[1]);
	append_to_envs(&export->env, key_value[0], key_value[1]);
	free_key_value(key_value);
	return (1);
}

static int	is_invalid_identifier(char *arg)
{
	if ((arg[0] == '=') || dash_before_equal(arg))
		return (1);
	return (0);
}

static int	new_export(t_export *export, t_command *command)
{
	int	i;
	int	j;

	i = 1;
	while (command->args[i])
	{
		j = 0;
		if (is_invalid_identifier(command->args[i]))
			return (write(2, "WhatTheShell: export: `", 23),
				write(2, command->args[i], ft_strlen(command->args[i])),
				write(2, "': not a valid identifier\n", 26), 1);
		while (command->args[i][j])
		{
			if (append_export(export, command, i)
				|| add_export(export, command, i))
				break ;
			if (!command->args[i][j + 1])
				my_setenv(&export->export, command->args[i], NULL);
			j++;
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_export *export, t_command *command)
{
	char	**export_tab;
	char	*equal;
	int		i;

	if (command->args[1])
		return (new_export(export, command));
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
