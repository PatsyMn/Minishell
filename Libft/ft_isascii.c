/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:Libft/ft_isascii.c
/*   ft_isascii.c                                       :+:      :+:    :+:   */
========
/*   minishell.h                                        :+:      :+:    :+:   */
>>>>>>>> main:minishell.h
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:Libft/ft_isascii.c
/*   Created: 2025/03/31 09:45:28 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/03/31 09:45:29 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include<stdio.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

// int main()
// {
//     printf("%d\n", ft_isascii(442));
// }
========
/*   Created: 2025/08/15 17:33:22 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/01 12:54:49 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== LIBRARIES ========== */
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

#endif
>>>>>>>> main:minishell.h
