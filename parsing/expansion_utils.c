/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:46:10 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/01 14:28:38 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*get_env_value(char *var_name, char **env_copy)
{
	int	i;
	int	len;

	if (!var_name || !env_copy)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], var_name, len) == 0
			&& env_copy[i][len] == '=')
			return (env_copy[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_var_name(char *str)
{
	int		i;
	char	*var_name;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (NULL);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	var_name[i] = '\0';
	while (--i >= 0)
		var_name[i] = str[i];
	return (var_name);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
