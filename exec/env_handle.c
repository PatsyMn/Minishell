/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:20:03 by mbores            #+#    #+#             */
/*   Updated: 2025/10/10 16:44:09 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void new_env(t_env **env, t_env *tmp, char *var, char *content)
{
    t_env   *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return ;
    node->key = ft_strdup(var);
    free(var);
    if (content)
    {
        node->content = ft_strdup(content);
        free(content);
    }
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

char    *my_getenv(t_env *env, char *var)
{
    while (env) {
        if (!ft_strncmp(env->key, var, ft_strlen(var)))
            return (env->content);
        env = env->next;
    }
    return (NULL);
}

void    my_setenv(t_env **env, char *var, char *content)
{
    t_env   *tmp;
    int     len;

    tmp = *env;
    len = ft_strlen(var);
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, var, len) && tmp->key[len] == '\0')
        {
            free(tmp->content);
            tmp->content = ft_strdup(content);
            free(content);
            return ;
        }
        tmp = tmp->next;
    }
    new_env(env, tmp, var, content);
}
