/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:21 by mbores            #+#    #+#             */
/*   Updated: 2025/10/20 15:34:52 by mbores           ###   ########.fr       */
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

static int	is_printable_token(t_token *token)
{
	if (token->type == T_APPEND_OUT || token->type == T_FILENAME
		|| token->type == T_HEREDOC || token->type == T_REDIR_IN
		|| token->type == T_REDIR_OUT)
		return (0);
	return (1);
}

static void	echo_arg(t_token *token, int *printable)
{
	int		i;
	int		status_len;
	char	*status;

	i = 0;
	if (!is_printable_token(token))
		return ;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] == '?'
			&& token->type != T_SINGLE_QUOTE)
		{
			status = ft_itoa(g_status);
			status_len = ft_strlen(status);
			write(STDOUT_FILENO, status, status_len);
			free(status);
			i++;
		}
		else
		{
			write(STDOUT_FILENO, &token->value[i], 1);
			*printable = 1;
		}
		i++;
	}
}

int	builtin_echo(t_command *command, t_pipex *pipex)
{
	int		i;
	int		printable;
	t_token	*cur;

	cur = command->token_list->next;
	i = 1;
	printable = 0;
	while (command->args[i] && is_option_n(command->args[i]))
	{
		pipex->n = 1;
		i++;
		cur = cur->next;
	}
	while (cur)
	{
		echo_arg(cur, &printable);
		if (is_printable_token(cur) && cur->next && printable)
			write(STDOUT_FILENO, " ", 1);
		cur = cur->next;
	}
	if (!pipex->n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
