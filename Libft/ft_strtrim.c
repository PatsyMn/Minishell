/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:47:12 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 13:02:26 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && char_in_set(s1[start], set) == 1)
		start++;
	while (end > start && char_in_set(s1[end], set) == 1)
		end--;
	new_s = malloc(sizeof(char) * (end - start + 2));
	if (!new_s)
		return (NULL);
	while (start <= end)
		new_s[i++] = s1[start++];
	new_s[i] = '\0';
	return (new_s);
}

// int main()
// {
// 	char *s1 = "ffhello";
// 	char *set = "ff";
// 	printf("%s \n", ft_strtrim(s1, set));
// }
