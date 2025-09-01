/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:46:05 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:46:06 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*new_src;
	unsigned char		*new_dest;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	new_src = src;
	new_dest = dest;
	while (i < n)
	{
		new_dest[i] = new_src[i];
		i++;
	}
	return (dest);
}

// int main()
// {
// 	size_t n = 8;
// 	char src[] = "sunshine";
//     char dest[9];
//     ft_memcpy(dest, src, n + 1);
//     printf("src: %s\n", src);
//     printf("dest: %s\n", dest);
// }
