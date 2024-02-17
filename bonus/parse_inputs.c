/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:55:59 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/17 01:01:55 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse_commands(int argc, char **argv, t_cmd **cmd_list)
{
	int	idx;

	idx = 2;
	while (idx < argc -1)
		ft_cmdadd_back(cmd_list, ft_cmdnew(argv[idx++]));
}

static char	*parse_file(char **str_list, int idx)
{
	char	*file;

	if (str_list[idx])
		file = ft_strdup(str_list[idx]);
	else
		file = NULL;
	return (file);
}

void	parse_input(int argc, char **argv, char *files[2], t_cmd **cmd_list)
{
	if (argc != 5)
		exit (127);
	files[STDIN_FILENO] = parse_file(argv, 1);
	files[STDOUT_FILENO] = parse_file(argv, argc - 1);
	parse_commands(argc, argv, cmd_list);
}