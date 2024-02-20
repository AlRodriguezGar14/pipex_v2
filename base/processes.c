/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:30 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/20 04:17:18 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		unix_error("pipe error", NULL);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		unix_error("fork error", NULL);
	return (pid);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*path;
	char	**exec_args;

	exec_args = ft_split(cmd, ' ');
	if (!exec_args)
		unix_error("split error", NULL);
	path = extract_path(envp, exec_args[0]);
	if (!path)
	{
		cleanup(exec_args);
		unix_error("path error", NULL);
	}
	ft_fd_printf(STDERR_FILENO, "Execute the program: %s\n", path);
	if (execve(path, exec_args, envp) == -1)
	{
		cleanup(exec_args);
		free(path);
		unix_error("execve error", NULL);
	}
}

void	in_process(char *file_read, int pipe_fd[2], char *cmd, char **envp)
{
	int	file_in;
	int	pid;

	if (access(file_read, F_OK) != 0)
		unix_error("file error", file_read);
	if (access(file_read, R_OK) != 0)
		unix_error("read error", file_read);
	file_in = open(file_read, O_RDONLY, 0444);
	if (file_in == -1)
		unix_error("error when reading the file", file_read);
	pid = fork_process();
	if (pid == 0)
	{
		close(pipe_fd[STDIN]);
		dup2(pipe_fd[STDOUT], STDOUT);
		dup2(file_in, STDIN);
		exec_cmd(cmd, envp);
	}
}

void	out_process(char *file_write, int pipe_fd[2], char *cmd, char **envp)
{
	int	file_out;
	int	pid;

	file_out = open(file_write, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
		unix_error("write error", file_write);
	pid = fork_process();
	if (pid == 0)
	{
		close(pipe_fd[STDOUT]);
		dup2(pipe_fd[STDIN], STDIN);
		dup2(file_out, STDOUT);
		exec_cmd(cmd, envp);
	}
}
