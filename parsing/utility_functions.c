/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:59:40 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/22 18:48:44 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_with_escape(const char *input, int start, int end)
{
	char	*word;
	int		i;
	int		j;

	if (!input || start < 0 || end <= start)
		return (NULL);
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		if (input[i] == '\\' && i + 1 < end)
		{
			i++;
			word[j++] = input[i++];
		}
		else
			word[j++] = input[i++];
	}
	word[j] = '\0';
	return (word);
}