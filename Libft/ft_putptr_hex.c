/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:09:56 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 10:17:32 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_hex(unsigned long adress, int *count)
{
	if (adress >= 16)
	{
		ft_putptr_hex(adress / 16, count);
		*count += write(1, &"0123456789abcdef"[adress % 16], 1);
	}
	else
		*count += write(1, &"0123456789abcdef"[adress % 16], 1);
}
// int main()
// {
//     unsigned long adress = 255;
//     ft_putptr_hex(adress);
// }