/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:30 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/13 18:13:40 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unix_error(char *mssg)
{
	ft_fd_printf(STDERR_FILENO, "%s: %s\n", mssg, strerror(errno));
	exit (0);
}

void	create_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		unix_error("pipe error");
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		unix_error("fork error");
	return (pid);
}
