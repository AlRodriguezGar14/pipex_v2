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

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_list;
	t_cmd	*tmp;
	char	*files[2];
	int		pipe_fd[2];
	int		status;

	cmd_list = NULL;
	parse_input(argc, argv, files, &cmd_list);
	create_pipes(pipe_fd);
	tmp = cmd_list;
	while (tmp)
	{
		in_process(files[STDIN_FILENO], pipe_fd, tmp->content, envp);
		tmp = tmp->next;
		while (tmp->next != NULL)
			tmp = tmp->next;
		out_process(files[STDOUT_FILENO], pipe_fd, tmp->content, envp);
		tmp = tmp->next;
	}
	waitpid(-1, &status, 0);
	cleanup_struct(cmd_list);
	if (status != 0)
		return (status);
	return (0);
}
