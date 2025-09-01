/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:45:48 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 11:32:21 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int main()
// {
// 	char *str = "sunshine";
// 	char *str2 = "sunrise";
// 	void *content = str;
// 	void *content2 = str2;
// 	t_list *node = ft_lstnew(content);
// 	node->next = ft_lstnew(content2);
// 	printf("%s\n", (char*)node->content);
// 	printf("%s\n", (char*)node->next->content);
// 	free(node->next);
// 	free(node);
// }
