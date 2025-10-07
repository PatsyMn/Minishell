/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:52:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/07 12:17:41 by pmeimoun         ###   ########.fr       */
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

    if (envp)
    {
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
    return (NULL);
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

