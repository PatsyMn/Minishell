/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:11:36 by mbores            #+#    #+#             */
/*   Updated: 2025/10/14 14:56:48 by pmeimoun         ###   ########.fr       */
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
			if (ft_strncmp(env_tab[i], env_tab[j],
					ft_strlen(env_tab[i]) + 1) > 0)
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
