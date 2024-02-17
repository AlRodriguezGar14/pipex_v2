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


void mid_process(char *cmd, char **envp)
{
	int pid;

	pid = fork_process();

	if (pid == 0)
		exec_cmd(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_list;
	t_cmd	*tmp;
	char	*files[2];
	int 	idx;
	int		(*pipe_fd)[2];
	int		status;

	idx = -1;
	pipe_fd = malloc(sizeof(int) * argc - 3);
	if (!pipe_fd)
		unix_error("malloc error", NULL);
	while (++idx < argc -3)
	{
		create_pipes(pipe_fd[idx]);
		ft_printf("pipe_fd[%d]\n", idx);
	}
	cmd_list = NULL;
	parse_input(argc, argv, files, &cmd_list);
	tmp = cmd_list;
	idx = 0;
	while (tmp)
	{
		in_process(files[STDIN_FILENO], pipe_fd[idx], tmp->content, envp);
		tmp = tmp->next;
		while (tmp->next != NULL)
		{	
			dup2(pipe_fd[idx][0], STDIN_FILENO);
			dup2(pipe_fd[++idx][1], STDOUT_FILENO);
			mid_process(tmp->content, envp);
			tmp = tmp->next;
		}
		out_process(files[STDOUT_FILENO], pipe_fd[idx], tmp->content, envp);
		tmp = tmp->next;
	}
	waitpid(-1, &status, 0);
	cleanup_struct(cmd_list);
	if (status != 0)
		return (status);
	return (0);
}
