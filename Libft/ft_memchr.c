/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:45:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:45:58 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_s;

	i = 0;
	new_s = (unsigned char *)s;
	while (i < n)
	{
		if (new_s[i] == (unsigned char)c)
			return ((void *)&new_s[i]);
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	{
// 		char s[] = "hello sunshine";
// 		int c = 's';
// 		size_t n;
// 		n = 15;
// 		printf("%s \n",(char *)ft_memchr(s, c, n));
// 		return 0;
// 	}
// }
