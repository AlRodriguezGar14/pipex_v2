/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:06:26 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/14 08:04:30 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unix_error(char *mssg, char *str)
{
	if (!str)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", mssg, strerror(errno));
	else
		ft_fd_printf(STDERR_FILENO, "%s, %s: %s\n", str, mssg, strerror(errno));
	exit (1);
}

static void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int     i;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		i = 0;
		while (cmd_list->content[i])
			free(cmd_list->content[i++]);
		free(cmd_list->content);
		free(cmd_list);
		cmd_list = tmp;
	}
}void cleanup(t_cmd *cmd_list)
{
	if (cmd_list)
		free_cmd_list(cmd_list);
//	exit (1);
}
