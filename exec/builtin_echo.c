/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:21 by mbores            #+#    #+#             */
/*   Updated: 2025/10/15 11:35:52 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_option_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] != 'n')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

static void	echo_arg(char *arg, int *printable)
{
	int		i;
	int		status_len;
	char	*status;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?') // TODO: pb recupere 
		{
			status = ft_itoa(g_status);
			status_len = ft_strlen(status);
			write(STDOUT_FILENO, status, status_len);
			free(status);
			i += 2;
		}
		else
		{
			write(STDOUT_FILENO, &arg[i], 1);
			*printable = 1;
			i++;
		}
	}
}

int	builtin_echo(char **args, t_pipex *pipex)
{
	int	i;
	int	printable;

	i = 1;
	printable = 0;
	while (args[i] && is_option_n(args[i]))
	{
		pipex->n = 1;
		i++;
	}
	while (args[i])
	{
		echo_arg(args[i], &printable);
		if (args[i + 1] && printable)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!pipex->n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
