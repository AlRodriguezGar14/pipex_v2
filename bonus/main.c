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

void mid_process(char *cmd, char **envp, int pipe_in[2], int pipe_out[2])
{
    int pid = fork_process();
    if (pid == 0)
    {
		dup2(pipe_in[0], STDIN_FILENO);
		close(pipe_in[0]);
		close(pipe_in[1]);

		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_out[0]);
		close(pipe_out[1]);
        exec_cmd(cmd, envp);
    }
    if (pipe_in)
    	close(pipe_in[0]);
}

int main(int argc, char **argv, char **envp)
{
    t_cmd *cmd_list;
    t_cmd *tmp;
    char *files[2];
    int status;
    int file_in;
    int file_out;
    int pipe_fd[2] = {-1, -1};

    cmd_list = NULL;
    parse_input(argc, argv, files, &cmd_list);
    file_in = in_file_open(files[STDIN_FILENO]);
    file_out = out_file_open(files[STDOUT_FILENO]);
    tmp = cmd_list;

    while(tmp)
    {
        int next_pipe[2] = {-1, -1};
        if (tmp->next)
            create_pipes(next_pipe);
        else
            next_pipe[1] = file_out;
        if (tmp == cmd_list)
        {
            int in_pipe[2] = {file_in, -1};
            mid_process(tmp->content, envp, in_pipe, next_pipe);
        }
        else
            mid_process(tmp->content, envp, pipe_fd, next_pipe);
        if (pipe_fd[0])
            close(pipe_fd[0]);
        if (pipe_fd[1])
            close(pipe_fd[1]);
        pipe_fd[0] = next_pipe[0];
        pipe_fd[1] = next_pipe[1];
        tmp = tmp->next;
    }

    if (pipe_fd[0])
        close(pipe_fd[0]);

    waitpid(-1, &status, 0);
    cleanup_struct(cmd_list);
    if (status != 0)
        return (status);
    return (0);
}