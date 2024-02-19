/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/17 00:28:07by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    close_pipes(int pipe[2], int next_pipe[2])
{
    if (pipe && pipe[STDIN_FILENO])
        close(pipe[STDIN_FILENO]);
    if (pipe && pipe[STDOUT_FILENO])
        close(pipe[STDOUT_FILENO]);
    if (next_pipe && next_pipe[STDIN_FILENO])
        close(next_pipe[STDIN_FILENO]);
    if (next_pipe && next_pipe[STDOUT_FILENO])
        close(next_pipe[STDOUT_FILENO]);
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
		dup2(pipe_in[STDIN_FILENO], STDIN_FILENO);
		close(pipe_in[STDOUT_FILENO]);

		dup2(pipe_out[STDOUT_FILENO], STDOUT_FILENO);
		close(pipe_out[STDIN_FILENO]);
        exec_cmd(cmd, envp);
    }
    if (pipe_in)
    	close(pipe_in[STDIN_FILENO]);
}

void advance_pipe(int prev_pipe[2], int next_pipe[2])
{
    close_pipes(prev_pipe, NULL);
    prev_pipe[STDIN_FILENO] = next_pipe[STDIN_FILENO];
    prev_pipe[STDOUT_FILENO] = next_pipe[STDOUT_FILENO];
}

int main(int argc, char **argv, char **envp)
{
    t_cmd *cmd_list;
    t_cmd *head;
    char *files[2];
    int status;
    int pipe_fd[2];
    int next_pipe[2];

    cmd_list = NULL;
    parse_input(argc, argv, files, &cmd_list);
    head = cmd_list;
    while(cmd_list)
    {
        create_pipes(next_pipe);
        if (!cmd_list->next)
            next_pipe[1] = out_file_open(files[STDOUT_FILENO]);
        if (cmd_list == head)
            pipe_fd[STDIN_FILENO] = in_file_open(files[STDIN_FILENO]);
        run_process(cmd_list->content, envp, pipe_fd, next_pipe);
        advance_pipe(pipe_fd, next_pipe);
        cmd_list = cmd_list->next;
    }
    waitpid(-1, &status, 0);
    return (close_pipes(pipe_fd, next_pipe), cleanup_struct(head), status);
}