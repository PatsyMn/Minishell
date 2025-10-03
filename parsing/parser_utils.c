/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:27:03 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/10/03 13:38:37 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static char	*remove_quotes(char *str)
{
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len])
		len++;
	if (len < 2)
		return (str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"' && str[len
				- 1] == '"'))
	{
		new_str = ft_strdup_with_escape(str, 1, len - 1);
		if (!new_str)
		{
			free(str);
			return (NULL);
		}
		free(str);
		return (new_str);
	}
	return (str);
}*/

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
	int		size;
	char	**new_args;
	char	*clean_val;

	if (!val)
		return ;
	clean_val = ft_strdup(val);
	if (!clean_val)
		return ;
	size = get_args_size(cmd->args);
	new_args = malloc(sizeof(char *) * (size + 2));
	if (!new_args)
	{
		free(clean_val);
		return ;
	}
	copy_args(new_args, cmd->args, size);
	new_args[size] = clean_val;
	new_args[size + 1] = NULL;
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
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		// if (cmd->limiter)
		// 	free(cmd->limiter);
		free(cmd);
		cmd = tmp;
	}
}
