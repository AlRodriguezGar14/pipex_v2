/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 18:39:24 by alberrod         ###   ########.fr       */
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
	{
		while (pipe->cmd_list)
		{
			create_pipes(pipe->next_pipe);
			if (!pipe->cmd_list->next)
				pipe->next_pipe[1] = out_file_open(pipe->files[STDOUT]);
			if (pipe->cmd_list == pipe->cmd_head)
				pipe->pipe_fd[STDIN] = in_file_open(pipe->files[STDIN]);
			ft_printf("cmd_list->content: %s\n", pipe->cmd_list->content);
			run_process(pipe->cmd_list->content, envp,
				pipe->pipe_fd, pipe->next_pipe);
			advance_pipe(pipe->pipe_fd, pipe->next_pipe);
			pipe->cmd_list = pipe->cmd_list->next;
		}
		exit (0);
	}
	waitpid(-1, &status, 0);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))
		unlink(pipe->files[STDIN]);
	return (close_pipes(pipe->pipe_fd, pipe->next_pipe),
		cleanup_struct(pipe), status);
}
