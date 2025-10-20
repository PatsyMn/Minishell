/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:20:03 by mbores            #+#    #+#             */
/*   Updated: 2025/10/20 18:07:18 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_env(t_env **env, t_env *tmp, char *var, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = var;
	if (content)
		node->content = content;
	else
		node->content = NULL;
	node->next = NULL;
	if (*env == NULL)
		*env = node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

char	*my_getenv(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->key, var, ft_strlen(var)))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

static int	modify_env(t_env *tmp, char *content)
{
	if (!tmp)
		return (0);
	free(tmp->content);
	if (content)
		tmp->content = ft_strdup(content);
	else
		tmp->content = NULL;
	return (1);
}

void	my_setenv(t_env **env, char *var, char *content)
{
	t_env	*tmp;
	char	*new_key;
	char	*new_value;
	int		len;

	if (!env || !var)
		return ;
	len = ft_strlen(var);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, len) && tmp->key[len] == '\0')
		{
			modify_env(tmp, content);
			return ;
		}
		tmp = tmp->next;
	}
	new_key = ft_strdup(var);
	new_value = NULL;
	if (content)
		new_value = ft_strdup(content);
	new_env(env, tmp, new_key, new_value);
}
