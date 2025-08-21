/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:10:25 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 10:13:08 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hex(unsigned int n, int uppercase, int *count)
{
	char	*strlow;
	char	*strup;

	strlow = "0123456789abcdef";
	strup = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_putnbr_hex(n / 16, uppercase, count);
		ft_putnbr_hex(n % 16, uppercase, count);
	}
	else
	{
		if (uppercase == 0)
			ft_putchar(strlow[n], count);
		else
			ft_putchar(strup[n], count);
	}
}
