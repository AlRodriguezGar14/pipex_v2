/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 06:13:46 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 20:44:09 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	in_file_open(char *file_read)
{
	int	file_in;

	if (access(file_read, F_OK) != 0)
		unix_error("file error", file_read);
	if (access(file_read, R_OK) != 0)
		unix_error("read error", file_read);
	file_in = open(file_read, O_RDONLY, 0444);
	if (file_in == -1)
		unix_error("error when reading the file", file_read);
	return (file_in);
}

int	out_file_open(char *file_write)
{
	int	file_out;

	// file_out = open(file_write, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file_out = open(file_write, O_WRONLY | O_TRUNC, 0644);
	if (file_out == -1)
		unix_error("write error", file_write);
	return (file_out);
}

void	out_file_create(char *file_write)
{
	int	file_out;

	if (access(file_write, F_OK) != 0)
	{
		file_out = open(file_write, O_CREAT, 0644);	
		close (file_out);
	}
}