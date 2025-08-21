/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:46:30 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/01 13:41:14 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c_delimiter)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] != c_delimiter) && ((str[i + 1] == c_delimiter) || str[i
					+ 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_copy_word(const char *src, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (src[i] != '\0' && start < end)
	{
		word[i] = src[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char **in_tab)
{
	int	i;

	i = 0;
	if (in_tab)
	{
		while (in_tab[i])
		{
			free(in_tab[i]);
			i++;
		}
		free(in_tab);
	}
}

char	**fill_tab(char **in_tab, const char *s, char c, int start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i > start)
		{
			in_tab[j] = ft_copy_word(s, start, i);
			if (!in_tab[j])
			{
				ft_free(in_tab);
				return (NULL);
			}
			j++;
		}
	}
	in_tab[j] = NULL;
	return (in_tab);
}

char	**ft_split(char const *s, char c)
{
	char	**in_tab;

	if (!s)
		return (NULL);
	in_tab = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!in_tab)
		return (NULL);
	in_tab = fill_tab(in_tab, s, c, 0);
	return (in_tab);
}

// int main()
// {
// 	char *s = "NULL";
// 	char c = ' ';
// 	char **result = ft_split(s, c);
// 	int i = 0;

// 	while (result[i] != NULL)
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// }