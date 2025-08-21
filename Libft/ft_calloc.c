/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:45:10 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:45:11 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <string.h>
// #include <ctype.h>

// #define GREEN "\033[0;32m"
// #define RED "\033[0;31m"
// #define RESET "\033[0m"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

// int main(void)
// {
//     size_t count = 5, size = sizeof(int);
//     int *ptr1 = calloc(count, size);
//     int *ptr2 = ft_calloc(count, size);

//     if (!ptr1 || !ptr2)
//     {
//         printf(RED "Erreur d'allocation de mémoire ❌\n" RESET);
//         return 1;
//     }

//     if (memcmp(ptr1, ptr2, count * size) == 0)
//         printf(GREEN "Test ft_calloc(5, sizeof(int)) ✅\n" RESET);
//     else
//         printf(RED "Test ft_calloc(5, sizeof(int)) ❌\n" RESET);

//     free(ptr1);
//     free(ptr2);
// }
