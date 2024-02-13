/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/13 19:38:59 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static void print_inputs(char *files[2], t_cmd *cmd_list)
{
	ft_fd_printf(STDOUT_FILENO, "files: %s, %s\n", files[0], files[1]);
	ft_cmditer(cmd_list, print_commands);
}

void	free_path(char **path)
{
	int	idx;

	idx = 0;
	while (path[idx])
		free(path[idx++]);
	free(path);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		free(cmd_list->content);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	exec_cmd(t_cmd *cmd_list, char **envp)
{
	char	*path;

	path = extract_path(envp, cmd_list->content[0]);
	if (!path)
	{
		ft_fd_printf(STDERR_FILENO, "The program '%s' doesn't exist\n", cmd_list->content[0]);
		return ;
	}
	ft_fd_printf(STDERR_FILENO, "Execute the program: %s\n", path);
	execve(path, cmd_list->content, envp);
}

void	child_process(char *files[2], int pipe_fd[2], t_cmd *cmd_list, char **envp)
{
	char 	*file_read;
	int 	fd_in;

	close(pipe_fd[STDIN_FILENO]);
	file_read = ft_strdup(files[STDIN_FILENO]);
	if (access(file_read, F_OK) != 0)
		unix_error("no such file or directory");
	if (access(file_read, R_OK) != 0)
		unix_error("can't read the input file");

	fd_in = open(file_read, O_RDONLY, 0777);
	if (fd_in == -1)
		unix_error("error when reading the file");
	dup2(pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	exec_cmd(cmd_list, envp);
}

void	parent_process(char *files[2], int pipe_fd[2], t_cmd *cmd_list, char **envp)
{
	char	*file_write;
	int 	fd_out;

	close(pipe_fd[STDOUT_FILENO]);
	file_write = ft_strdup(files[STDOUT_FILENO]);
	fd_out = open(file_write, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		unix_error("error when writing to file");
	dup2(pipe_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	exec_cmd(cmd_list, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*cmd_list;
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (argc != 5)
		exit (2);
	cmd_list = NULL;
	parse_input(argc, argv, files, &cmd_list);
	print_inputs(files, cmd_list);

	create_pipes(pipe_fd);
	pid = fork_process();
	if (pid == 0)
	{
		ft_printf("child process\n");
		child_process(files, pipe_fd, cmd_list, envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_printf("exit status: %d\n", status);
	ft_printf("parent process\n");
	child_process(files, pipe_fd, cmd_list->next, envp);
	free_cmd_list(cmd_list);
	return (0);
}
