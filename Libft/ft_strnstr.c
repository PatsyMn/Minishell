/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:47:05 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:50:54 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *string, const char *substring, size_t n)
{
	size_t	i;
	size_t	j;

	if (*substring == '\0')
		return ((char *)string);
	i = 0;
	while (i < n && string[i] != '\0')
	{
		j = 0;
		while (string[i + j] == substring[j] && (i + j) < n)
		{
			j++;
			if (substring[j] == '\0')
				return ((char *)&string[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char *string = "hello sunshine";
// 	char *substring = "sunshine";
// 	size_t n = 15;
// 	printf("%s \n", ft_strnstr(string, substring, n));
// }
