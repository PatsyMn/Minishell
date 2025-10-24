/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:49:08 by mbores            #+#    #+#             */
/*   Updated: 2025/10/24 15:23:19 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoll(const char *nptr)
{
	long long	i;
	long long	sign_nbr;
	long long	nb;

	i = 0;
	sign_nbr = 1;
	nb = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign_nbr = sign_nbr * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + nptr[i] - '0';
		i++;
	}
	return (nb * sign_nbr);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(const char *str)
{
	long long	n;
	int			i;

	i = 0;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (n > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	builtin_exit(t_command *command, t_export *export, t_pipex *pipex)
{
	long long	exit_code;

	write(1, "exit\n", 5);
	if (!command->args[1])
		exit(g_status);
	if (!is_numeric(command->args[1]) || !check_overflow(command->args[1]))
	{
		write(2, "WhatTheShell: exit: ", 20);
		write(2, command->args[1], ft_strlen(command->args[1]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	if (command->args[2])
	{
		write(2, "WhatTheShell: exit: too many arguments\n", 39);
		return (1);
	}
	exit_code = ft_atoll(command->args[1]);
	free_env_chained(export->env);
	free_env_chained(export->export);
	free(export);
	free(pipex);
	free_commands(command);
	rl_clear_history();
	exit((unsigned char)exit_code);
}
