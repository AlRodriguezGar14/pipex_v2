/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/16 02:33:26 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		count;
	int		status;

	if (argc != 5)
		exit (2);
	create_pipes(pipe_fd);
	count = -1;
	while (++count < 2)
	{
		if (count == 0)
			in_process(argv[1], pipe_fd, argv[2], envp);
		else if (count == 1)
			out_process(argv[4], pipe_fd, argv[3], envp);
	}
	waitpid(-1, &status, 0);
	if (status != 0)
		return (status);
	return (0);
}
