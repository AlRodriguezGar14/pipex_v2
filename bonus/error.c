/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:06:26 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 21:46:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unix_error(char *mssg, char *str)
{
	if (!str)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", mssg, strerror(errno));
	else
		ft_fd_printf(STDERR_FILENO, "<%s> %s: %s\n",
			str, mssg, strerror(errno));
	exit (127);
}

void	cleanup(char **exec_args)
{
	char	**tmp;

	tmp = exec_args;
	if (!exec_args)
		return ;
	while (*tmp)
		free(*tmp++);
	free(exec_args);
}
