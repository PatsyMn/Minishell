/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:10:09 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 10:16:02 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned_putnbr(unsigned int n, int *count)
{
	if (n >= 10)
	{
		ft_unsigned_putnbr(n / 10, count);
		ft_unsigned_putnbr(n % 10, count);
	}
	else
		ft_putchar(n + '0', count);
}
