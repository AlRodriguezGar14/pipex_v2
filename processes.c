/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:30 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/15 01:00:51 by alberrod         ###   ########.fr       */
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

	close(pipe_fd[STDIN_FILENO]);
	if (access(file_read, F_OK) != 0)
		unix_error("file error", file_read);
	if (access(file_read, R_OK) != 0)
		unix_error("read error", file_read);
	file_in = open(file_read, O_RDONLY, 0777);
	if (file_in == -1)
		unix_error("error when reading the file", file_read);
	dup2(pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);
	exec_cmd(cmd, envp);
}

void	out_process(char *file_write, int pipe_fd[2], char *cmd, char **envp)
{
	int	file_out;

	close(pipe_fd[STDOUT_FILENO]);
	file_out = open(file_write, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
		unix_error("write error", file_write);
	dup2(pipe_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	exec_cmd(cmd, envp);
}
