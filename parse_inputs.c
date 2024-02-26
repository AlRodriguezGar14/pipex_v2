/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:45:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/26 10:32:35 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:55:59 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 21:36:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse_commands(int argc, char **argv, t_cmd **cmd_list, int idx)
{
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

static void	parse_here_doc(char **argv)
{
	int		in_file;
	char	*line;

	in_file = open("/tmp/here_doc", O_CREAT | O_RDWR, 0644);
	line = get_next_line(STDIN);
	while (ft_strncmp(line, argv[2], ft_strlen(argv[2])))
	{
		write(in_file, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN);
	}
	free(line);
	close(in_file);
}

void	parse_input(int argc, char **argv, char *files[2], t_pipe *pipe)
{
	int	idx;

	idx = 2;
	files[STDOUT] = parse_file(argv, argc - 1);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		ft_printf("Write your input followed by new-line:\n");
		parse_here_doc(argv);
		files[STDIN] = ft_strdup("/tmp/here_doc");
		pipe->write_mode = O_APPEND;
		idx++;
	}
	else
		files[STDIN] = parse_file(argv, 1);
	parse_commands(argc, argv, &pipe->cmd_list, idx);
}
