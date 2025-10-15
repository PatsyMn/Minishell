/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:31:23 by mbores            #+#    #+#             */
/*   Updated: 2025/10/15 13:39:59 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_sep(const char *s, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (s[i] != sep[i])
			return (0);
		i++;
	}
	return (1);
}

static int	word_count(const char *s, const char *sep)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = 0;
	while (sep[len])
		len++;
	while (s[i])
	{
		if (is_sep(s + i, sep))
			i += len;
		else
		{
			count++;
			while (s[i] && !is_sep(s + i, sep))
				i++;
		}
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	fill_tab(char **tab, const char *s, const char *sep, int len)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_sep(s + i, sep))
			i += len;
		else
		{
			start = i;
			while (s[i] && !is_sep(s + i, sep))
				i++;
			tab[j] = word_dup(s, start, i);
			if (!tab[j])
				return (free_tab(tab), 0);
			j++;
		}
	}
	tab[j] = NULL;
	return (1);
}

char	**new_ft_split(const char *s, const char *sep)
{
	char	**tab;
	int		len;

	if (!s || !sep)
		return (NULL);
	len = 0;
	while (sep[len])
		len++;
	tab = malloc(sizeof(char *) * (word_count(s, sep) + 1));
	if (!tab)
		return (NULL);
	if (!fill_tab(tab, s, sep, len))
		return (NULL);
	return (tab);
}
