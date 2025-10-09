/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:27:03 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/09 11:17:41 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_args_size(char **args)
{
	int	size;

	size = 0;
	while (args && args[size])
		size++;
	return (size);
}

static void	copy_args(char **dest, char **src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

void	add_arg(t_command *cmd, char *val)
{
	int		args_count;
	char	**new_args;
	char	*arg_copy;

	if (!val)
		return ;
	arg_copy = ft_strdup(val);
	if (!*arg_copy)
		return ;
	args_count = get_args_size(cmd->args);
	new_args = malloc(sizeof(char *) * (args_count + 2));
	if (!new_args)
	{
		free(arg_copy);
		return ;
	}
	copy_args(new_args, cmd->args, args_count);
	new_args[args_count] = arg_copy;
	new_args[args_count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

static void	free_commands_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

void	free_commands(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_commands_args(cmd);
		if (cmd->token_list)
			free_tokens(cmd->token_list);
		free(cmd);
		cmd = tmp;
	}
}
