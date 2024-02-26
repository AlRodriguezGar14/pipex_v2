/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:45:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/26 10:32:05 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:20:58 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/21 20:42:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include "utils/libft.h"

# define NO_SUCH_FILE 2
# define CMD_NOT_FOUND 127
# define WRONG_INPUT 2
# define STDIN	0
# define STDOUT 1

typedef struct s_cmd
{
	char			*content;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	char	*files[2];
	int		pipe_fd[2];
	int		next_pipe[2];
	int		write_mode;
	t_cmd	*cmd_list;
	t_cmd	*cmd_head;
}	t_pipe;

// parse_inputs.c
//void	parse_input(int argc, char **argv, char *files[2], t_cmd **cmd_list);
void	parse_input(int argc, char **argv, char *files[2], t_pipe *pipe);
char	*extract_path(char **envp, char *cmd);

// build cmd list
t_cmd	*ft_cmdnew(void *content);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
// void	ft_cmditer(t_cmd *lst, void (*f)(char **));
void	cleanup_struct(t_pipe *pipe);

// deal with the processes
pid_t	fork_process(void);
void	run_pipes(t_pipe *pipe, char **envp);
void	run_process(char *cmd, char **envp, int pipe_in[2], int pipe_out[2]);
void	create_pipes(int pipe_fd[2]);
void	close_pipes(int pipe[2], int next_pipe[2]);
void	advance_pipe(int prev_pipe[2], int next_pipe[2]);

// error
void	unix_error(char *mssg, char *str);
void	cleanup(char **exec_args);

// deal with files
int		in_file_open(char *file_read);
int	out_file_open(char *file_write, int write_mode);
void	out_file_create(char *file_write);

#endif
