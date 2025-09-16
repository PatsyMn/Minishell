/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:28:09 by mbores            #+#    #+#             */
/*   Updated: 2025/09/12 13:40:01 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    open_files(t_command *command)
{
    if (command->infile)
        command->infile_fd = open(command->infile, O_RDONLY);
    if (command->append && command->outfile)
        command->outfile_fd = open(command->outfile,
            O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (command->outfile)
        command->outfile_fd = open(command->outfile,
            O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
