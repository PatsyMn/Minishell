/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:09:47 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 11:41:57 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_formats(char c, va_list args, int *count)
{
	if (c == 'c')
		ft_putchar((char)va_arg(args, int), count);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (c == 'p')
	{
		ft_formats_putptr(args, count);
	}
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (c == 'u')
		ft_unsigned_putnbr(va_arg(args, int), count);
	else if (c == 'x')
		ft_putnbr_hex(va_arg(args, unsigned int), 0, count);
	else if (c == 'X')
		ft_putnbr_hex(va_arg(args, unsigned int), 1, count);
	else if (c == '%')
		ft_put_percent(count);
}
