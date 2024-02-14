/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:20:58 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/14 07:36:40 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "utils/libft.h"

// definition of errors
# define NO_SUCH_FILE 2
# define CMD_NOT_FOUND 127
# define WRONG_INPUT 2

typedef struct s_cmd
{
	char			**content;
	struct s_cmd	*next;
}	t_cmd;

// generate_cmd_list_utils.c
t_cmd	*ft_cmdnew(void *content);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmditer(t_cmd *lst, void (*f)(char **));
void	print_commands(char **cmd_lst);

// parse_inputs.c
//char	**extract_path(char **envp);
char	*extract_path(char **envp, char *cmd);
void	parse_input(int argc, char **argv, t_cmd **cmd_list);

// deal with the processes
pid_t   fork_process(void);
void	create_pipes(int pipe_fd[2]);
void	exec_cmd(t_cmd *cmd_list, char **envp);
void	in_process(char *file_read, int pipe_fd[2], t_cmd *cmd_list, char **envp);
void	out_process(char *file_write, int pipe_fd[2], t_cmd *cmd_list, char **envp);

// error
void	unix_error(char *mssg, char *str);
void	cleanup(t_cmd *cmd_list);

#endif
