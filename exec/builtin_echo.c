/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:21 by mbores            #+#    #+#             */
/*   Updated: 2025/10/15 12:09:01 by mbores           ###   ########.fr       */
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

static void	echo_arg(t_token *token, int *printable)
{
	int		i;
	int		status_len;
	char	*status;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] == '?'
			&& token->type != T_SINGLE_QUOTE)
		{
			status = ft_itoa(g_status);
			status_len = ft_strlen(status);
			write(STDOUT_FILENO, status, status_len);
			free(status);
			i += 2;
		}
		else
		{
			write(STDOUT_FILENO, &token->value[i], 1);
			*printable = 1;
			i++;
		}
	}
}

int	builtin_echo(t_command *command, t_pipex *pipex)
{
	int		i;
	int		printable;
	t_token	*cur;

	i = 1;
	printable = 0;
	while (command->args[i] && is_option_n(command->args[i]))
	{
		pipex->n = 1;
		i++;
	}
	cur = command->token_list->next;
	while (cur)
	{
		echo_arg(cur, &printable);
		if (cur->next && printable)
			write(STDOUT_FILENO, " ", 1);
		cur = cur->next;
	}
	if (!pipex->n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
