/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:46:50 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:46:51 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;

	i = 0;
	if (dsize == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0' && i + 1 < dsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// int main()
// {
// 	size_t dsize = 4;
// 	const char *src = "sunshine";
// 	char dst[4];
// 	ft_strlcpy(dst, src, dsize);
// 	printf("%zu\n", ft_strlen(src));
// }
