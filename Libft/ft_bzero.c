/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:44:52 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:44:53 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*new_s;
	size_t			i;

	new_s = s;
	i = 0;
	while (i < n)
	{
		new_s[i] = 0;
		i++;
	}
}

// int main()
// {
// 	char test[] = "sunshine";
// 	ft_bzero(test, 9);
// 	write(1, test, 9);
// }
