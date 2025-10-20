/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:11:36 by mbores            #+#    #+#             */
/*   Updated: 2025/10/20 18:05:41 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_env_tab(char **env_tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_tab[i])
	{
		j = i + 1;
		while (env_tab[j])
		{
			if (ft_strncmp(env_tab[i], env_tab[j], ft_strlen(env_tab[i])
					+ 1) > 0)
			{
				tmp = env_tab[i];
				env_tab[i] = env_tab[j];
				env_tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	free_key_value(char **key_value)
{
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
}

void	add_to_envs(t_export *export, char *key, char *value)
{
	if (value)
	{
		my_setenv(&export->export, key, value);
		my_setenv(&export->env, key, value);
	}
	else
		my_setenv(&export->export, key, NULL);
}

void	append_to_envs(t_env **env, char *key, char *new_value)
{
	t_env	*tmp;
	char	*joined;
	char	*old_value;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
		{
			old_value = tmp->content;
			if (old_value)
				joined = ft_strjoin(old_value, new_value);
			else
				joined = ft_strdup(new_value);
			free(tmp->content);
			tmp->content = joined;
			return ;
		}
		tmp = tmp->next;
	}
	my_setenv(env, key, new_value);
}
