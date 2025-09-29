/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbores <mbores@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:46:51 by mbores            #+#    #+#             */
/*   Updated: 2025/09/11 14:09:18 by mbores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_temp_heredoc_file(char *file_name)
{
	int	file_fd;

	file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	return (file_fd);
}
