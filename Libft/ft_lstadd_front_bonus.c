/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:45:43 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:45:44 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int main ()
// {
// 	t_list* node = ft_lstnew("sunshine");
// 	t_list* node2 = ft_lstnew("sunrise");
// 	ft_lstadd_front(&node, node2);
// 	t_list *current = node;
// 	while (current)
// 	{
// 		printf("%s\n", (char *)current->content);
// 		current = current->next;
// 	}

// }
