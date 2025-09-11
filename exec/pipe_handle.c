/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:19:02 by mbores            #+#    #+#             */
/*   Updated: 2025/09/11 16:06:35 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_files(t_command *commands)
{
	commands->infile_fd = open(commands->infile, O_RDONLY);
	commands->outfile_fd = open(commands->outfile,
        O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (commands->infile_fd < 0)
        perror(commands->infile);
    if (commands->outfile_fd)
        perror(commands->outfile);
	return (0);
}
