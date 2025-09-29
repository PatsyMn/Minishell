/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:11:36 by mbores            #+#    #+#             */
/*   Updated: 2025/09/25 16:44:18 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    sort_env_tab(char **env_tab)
{
    int   i;
    int   j;
    char  *tmp;

    for (i = 0; env_tab[i]; i++)
    {
        for (j = i + 1; env_tab[j]; j++)
        {
            if (ft_strncmp(env_tab[i], env_tab[j], ft_strlen(env_tab[i])) > 0)
            {
                tmp = env_tab[i];
                env_tab[i] = env_tab[j];
                env_tab[j] = tmp;
            }
        }
    }
}
