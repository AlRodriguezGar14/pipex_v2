/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:06:26 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/14 08:32:39 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unix_error(char *mssg, char *str)
{
	if (!str)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", mssg, strerror(errno));
	else
		ft_fd_printf(STDERR_FILENO, "%s, %s: %s\n", str, mssg, strerror(errno));
	exit (1);
}

void cleanup(char **exec_args)
{
	while (*exec_args)
		free(*exec_args++);
}
