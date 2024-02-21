/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 21:48:16 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe	*init_struct(int argc, char **argv)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->cmd_list = NULL;
	parse_input(argc, argv, pipe->files, &pipe->cmd_list);
	pipe->cmd_head = pipe->cmd_list;
	pipe->pipe_fd[STDIN] = -1;
	pipe->pipe_fd[STDOUT] = -1;
	pipe->next_pipe[STDIN] = -1;
	pipe->next_pipe[STDOUT] = -1;
	return (pipe);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipe;
	int		pid;
	int		status;

	pipe = init_struct(argc, argv);
	pid = fork_process();
	if (pid == 0)
		run_pipes(pipe, envp);
	waitpid(pid, &status, 0);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))
		unlink(pipe->files[STDIN]);
	close_pipes(pipe->pipe_fd, pipe->next_pipe);
	cleanup_struct(pipe);
	if (status != 0)
		return (EXIT_FAILURE);
	return (0);
}
