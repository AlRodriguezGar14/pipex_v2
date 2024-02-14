/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/14 08:08:01 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void print_inputs(char **argv, t_cmd *cmd_list)
{
	ft_fd_printf(STDOUT_FILENO, "files: %s, %s\n", argv[1], argv[4]);
	ft_cmditer(cmd_list, print_commands);
}


int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_list;
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (argc != 5)
		exit (2);
	cmd_list = NULL;
	parse_input(argc, argv, &cmd_list);
	print_inputs(argv, cmd_list);
	create_pipes(pipe_fd);
	pid = fork_process();
	if (pid == 0)
		in_process(argv[1], pipe_fd, cmd_list, envp);
	waitpid(pid, &status, 0);
	if (status != 0)
	{
		cleanup(cmd_list);
		exit (status);
	}
	out_process(argv[4], pipe_fd, cmd_list->next, envp);
	return (0);
}
