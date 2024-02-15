/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/15 23:23:02 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (argc != 5)
		exit (2);
	create_pipes(pipe_fd);
	pid = fork_process();
	if (pid == 0)
		in_process(argv[1], pipe_fd, argv[2], envp);
	out_process(argv[4], pipe_fd, argv[3], envp);
	waitpid(pid, &status, 0);
	if (status != 0)
		exit (status);
	return (0);
}
