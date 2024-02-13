/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/13 14:40:47 by alberrod         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*cmd_list;
	char	**path;
//	int		fd_pipe[2];
//	int		pid;

	if (argc != 5)
		exit (2);
	cmd_list = NULL;
	path = extract_path(envp);
	parse_input(argc, argv, files, &cmd_list);

	print_inputs(files, cmd_list, path);
	return (0);
}
