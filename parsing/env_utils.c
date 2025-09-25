/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:52:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/24 16:41:41 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env_node(char *str)
{
	t_env   *node;
    char    *equal_pos;
    size_t  name_len;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    equal_pos = ft_strchr(str, '=');
    if (equal_pos)
    {
        name_len = equal_pos - str;
        node->key = ft_substr(str, 0, name_len);
        node->content = ft_strdup(equal_pos + 1);
    }
    else
    {
        node->key = ft_strdup(str);
        node->content = NULL;
    }
    node->next = NULL;
    return (node);
}

t_env	*copy_env_chained(char **envp)
{
	t_env *head;
    t_env *tail;
    t_env *node;
    int i;

	head = NULL;
	tail = NULL;
	i = 0;
    while (envp[i])
    {
        node = new_env_node(envp[i]);
        if (!node)
            return (NULL);
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
        i++;
    }
    return (head);
}

void	free_env_chained(t_env *env)
{
	t_env	*next_node;

	while (env)
	{
		next_node = env->next;
		free(env->key);
        if (env->content)
		    free(env->content);
		free(env);
		env = next_node;
	}
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

// char	**copy_env(char **envp)
// {
// 	int		i;
// 	char	**copy;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	copy = malloc(sizeof(char *) * (i + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		copy[i] = ft_strdup(envp[i]);
// 		if (!copy[i])
// 		{
// 			while (i--)
// 				free(copy[i]);
// 			free(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

// char	*get_env_value(char *var_name, char **env_copy)
// {
// 	int	i;
// 	int	len;

// 	if (!var_name || !env_copy)
// 		return (NULL);
// 	len = ft_strlen(var_name);
// 	i = 0;
// 	while (env_copy[i])
// 	{
// 		if (ft_strncmp(env_copy[i], var_name, len) == 0
// 			&& env_copy[i][len] == '=')
// 			return (env_copy[i] + len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }
