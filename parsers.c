/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:25:03 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/14 08:34:44 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_path(char **envp, char *cmd)
{
	char	**path_env;
	char	**path_array;
	char	*exec_path;

	path_array = ft_calloc(1, 1);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_env = ft_split(*envp, '=');
			path_array = ft_split(path_env[1], ':');
			break ;
		}
		envp++;
	}
	while (*path_array)
	{
		exec_path = ft_sprintf("%s/%s", *path_array, cmd);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		path_array++;
	}
	free(exec_path);
	return (NULL);
}
