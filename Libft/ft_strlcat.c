/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:46:47 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:46:48 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dsize)
	{
		i++;
	}
	if (i == dsize)
	{
		return (dsize + ft_strlen(src));
	}
	while (src[j] != '\0' && i < dsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}

// int main()
// {
// 	char dst[42] = "hello";
// 	const char *src = "sunshine";
// 	size_t dsize = 9;
// 	ft_strlcat(dst, src, dsize);
// 	printf("dest : %s\n", dst);
// }
