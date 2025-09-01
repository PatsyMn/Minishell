/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats_putptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:42:11 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 11:49:11 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_formats_putptr(va_list args, int *count)
{
	unsigned long	address;

	address = va_arg(args, unsigned long);
	if (address == 0)
		*count += write(1, "(nil)", 5);
	else
	{
		*count += write(1, "0x", 2);
		ft_putptr_hex(address, count);
	}
}
