/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:10:03 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 10:16:25 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	while (str[i] != '\0')
	{
		*count += write(1, &str[i], 1);
		i++;
	}
}
