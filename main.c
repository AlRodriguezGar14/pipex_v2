/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/13 16:19:03 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static void print_inputs(char *files[2], t_cmd *cmd_list, char **path)
{
	while(*path)
		ft_fd_printf(STDOUT_FILENO, "path: %s\n", *path++);
	ft_fd_printf(STDOUT_FILENO, "......\n");
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

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	char	**path;
	t_cmd	*cmd_list;
	pid_t   pid;
	int    status;
//	int		fd_pipe[2];

	if (argc != 5)
		exit (2);
	cmd_list = NULL;
	path = extract_path(envp);
	parse_input(argc, argv, files, &cmd_list);
	print_inputs(files, cmd_list, path);


	pid = fork_process();
	if (pid == 0)
	{
		ft_printf("child process\n");
		char *file = ft_sprintf("/bin/%s", cmd_list->content[0]);
		execve(file, cmd_list->content, envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_printf("exit status: %d\n", status);
	ft_printf("parent process\n");
	free_path(path);
	free_cmd_list(cmd_list);
	return (0);
}
