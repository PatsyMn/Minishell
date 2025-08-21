/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:46:41 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:46:42 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void test_tolower(unsigned int i, char *s)
// {
// 	(void)i;
// 	if (*s >= 'A' && *s <= 'Z')
// 		*s += 32;
// }

// int main ()
// {
// 	char* s = ft_strdup("SUNSHINEAAAAAA");
// 	ft_striteri(s, test_tolower);
// 	printf("%s\n", s);
// }
