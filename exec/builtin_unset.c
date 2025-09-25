/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:53:32 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 11:54:34 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_env_node(t_env *node)
{
    if (!node)
        return ;
    free(node->key);
    if (node->content)
        free(node->content);
    free(node);
}

static void unset_from_list(t_env **list, char *var)
{
    t_env *curr;
    t_env *prev;
    t_env *tmp;

    curr = *list;
    prev = NULL;
    while (curr)
    {
        if (!ft_strncmp(curr->key, var, ft_strlen(var))
            && curr->key[ft_strlen(var)] == '\0')
        {
            tmp = curr->next;
            if (prev)
                prev->next = tmp;
            else
                *list = tmp;
            free_env_node(curr);
            curr = tmp;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

int builtin_unset(t_export *export, t_command *command)
{
    int i;

    if (!command->args[1])
        return (1);
    i = 1;
    while (command->args[i])
    {
        unset_from_list(&export->export, command->args[i]);
        unset_from_list(&export->env, command->args[i]);
        i++;
    }
    return (1);
}
