/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:30 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/20 03:07:10 by alberrod         ###   ########.fr       */
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
	if (execve(path, exec_args, envp) == -1)
	{
		cleanup(exec_args);
		free(path);
		unix_error("execve error", NULL);
	}
}
