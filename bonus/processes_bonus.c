/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:30 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 19:16:18 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		unix_error("fork error", NULL);
	return (pid);
}

static void	exec_cmd(char *cmd, char **envp)
{
	char	*path;
	char	**exec_args;

	exec_args = ft_split(cmd, ' ');
	if (!exec_args)
		unix_error("split error", NULL);
	path = extract_path(envp, exec_args[0]);
	if (!path)
		unix_error("command error", exec_args[0]);
	if (execve(path, exec_args, envp) == -1)
	{
		cleanup(exec_args);
		free(path);
		unix_error("execve error", NULL);
	}
}

void	run_process(char *cmd, char **envp, int pipe_in[2], int pipe_out[2])
{
	int	pid;

	pid = fork_process();
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
