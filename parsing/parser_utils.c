/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:27:03 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/09/01 13:07:00 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str)
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
}

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
	clean_val = remove_quotes(val);
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
void	handle_redirection_in(t_command *cmd, t_token **token)
{
	t_token	*redir;
	t_token	*file;

	if (!(*token) || !(*token)->next)
		return ;
	redir = *token;
	file = (*token)->next;
	if (redir->type == T_REDIR_IN)
	{
		cmd->infile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->heredoc = 0;
	}
	else if (redir->type == T_HEREDOC)
	{
		cmd->infile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->heredoc = 1;
	}
	*token = file;
}

void	handle_redirection_out(t_command *cmd, t_token **token)
{
	t_token	*redir;
	t_token	*file;

	if (!(*token) || !(*token)->next)
		return ;
	redir = *token;
	file = (*token)->next;
	if (redir->type == T_REDIR_OUT)
	{
		cmd->outfile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->append = 0;
	}
	else if (redir->type == T_APPEND_OUT)
	{
		cmd->outfile = ft_strdup_with_escape(file->value, 0,
				ft_strlen(file->value));
		cmd->append = 1;
	}
	*token = file;
}
void	handle_redirection(t_command *cmd, t_token **token)
{
	if (!token || !(*token))
		return ;
	if ((*token)->type == T_REDIR_IN || (*token)->type == T_HEREDOC)
		handle_redirection_in(cmd, token);
	else if ((*token)->type == T_REDIR_OUT || (*token)->type == T_APPEND_OUT)
		handle_redirection_out(cmd, token);
}
