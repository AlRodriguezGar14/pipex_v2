/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/20 04:25:27 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    close_pipes(int pipe[2], int next_pipe[2])
{
	if (pipe && pipe[STDIN])
		close(pipe[STDIN]);
	if (pipe && pipe[STDOUT])
		close(pipe[STDOUT]);
	if (next_pipe && next_pipe[STDIN])
		close(next_pipe[STDIN]);
	if (next_pipe && next_pipe[STDOUT])
		close(next_pipe[STDOUT]);
}

int	in_file_open(char *file_read)
{
	int file_in;
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
	int file_out;

	file_out = open(file_write, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
		unix_error("write error", file_write);
	return (file_out);
}

void run_process(char *cmd, char **envp, int pipe_in[2], int pipe_out[2])
{
	int pid = fork_process();
	if (pid == 0)
	{
		dup2(pipe_in[STDIN], STDIN);
		close(pipe_in[STDOUT]);

		dup2(pipe_out[STDOUT], STDOUT);
		close(pipe_out[STDIN]);
		exec_cmd(cmd, envp);
	}
	if (pipe_in)
		close(pipe_in[STDIN]);
}

void advance_pipe(int prev_pipe[2], int next_pipe[2])
{
	close_pipes(prev_pipe, NULL);
	prev_pipe[STDIN] = next_pipe[STDIN];
	prev_pipe[STDOUT] = next_pipe[STDOUT];
}

t_pipe  *init_struct(int argc, char **argv)
{
	t_pipe  *pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->cmd_list = NULL;
	parse_input(argc, argv, pipe->files, &pipe->cmd_list);
	pipe->cmd_head = pipe->cmd_list;
	return (pipe);
}

int main(int argc, char **argv, char **envp)
{
	t_pipe  *pipe;
	int     status;

	pipe = init_struct(argc, argv);
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
	waitpid(-1, &status, 0);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))
		unlink(pipe->files[STDIN]);
	return (close_pipes(pipe->pipe_fd, pipe->next_pipe),
		cleanup_struct(pipe), status);
}
