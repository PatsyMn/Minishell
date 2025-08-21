/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:17:01 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/04/07 11:37:03 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_formats(char c, va_list args, int *count);
void	ft_formats_putptr(va_list args, int *count);
void	ft_putchar(char c, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putptr_hex(unsigned long adress, int *count);
void	ft_putnbr(int n, int *count);
void	ft_unsigned_putnbr(unsigned int n, int *count);
void	ft_putnbr_hex(unsigned int n, int uppercase, int *count);
void	ft_put_percent(int *count);

#endif
