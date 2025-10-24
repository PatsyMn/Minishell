/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:26:21 by mbores            #+#    #+#             */
/*   Updated: 2025/10/24 16:06:22 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		write(STDERR_FILENO, "pwd: error retrieving current directory: ", 41);
		write(STDERR_FILENO, "getcwd: cannot access parent directories: ", 42);
		write(STDERR_FILENO, "No such file or directory\n", 26);
		return (1);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(pwd);
	return (0);
}
