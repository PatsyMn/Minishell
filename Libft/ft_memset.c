/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:46:12 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:46:13 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*new_s;
	unsigned char	new_c;
	size_t			i;

	new_s = s;
	new_c = c;
	i = 0;
	while (i < n)
	{
		new_s[i] = new_c;
		i++;
	}
	return (s);
}

// int main()
// {
// 	size_t n = 42;
// 	char test[42];
// 	ft_memset(test, 'A', 42);
// 	write(1, test, 42);
// }
