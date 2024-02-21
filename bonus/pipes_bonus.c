/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 06:03:49 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 18:26:22 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		unix_error("pipe error", NULL);
}

void	close_pipes(int pipe[2], int next_pipe[2])
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

void	advance_pipe(int prev_pipe[2], int next_pipe[2])
{
	close_pipes(prev_pipe, NULL);
	prev_pipe[STDIN] = next_pipe[STDIN];
	prev_pipe[STDOUT] = next_pipe[STDOUT];
}
