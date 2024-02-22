/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:25:03 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/22 04:11:09 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char **array)
{
	int	idx;

	idx = 0;
	while (array[idx])
		free(array[idx++]);
	free(array);
}

static char	**get_path_array(char **envp)
{
	char	**path_env;
	char	**path_array;

	path_array = NULL;
	path_env = NULL;
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
	free_array(path_env);
	return (path_array);
}

char	*extract_path(char **envp, char *cmd)
{
	char	**path_array;
	char	*exec_path;
	int		idx;

	path_array = get_path_array(envp);
	if (!path_array)
		return (NULL);
	idx = 0;
	while (path_array[idx])
	{
		exec_path = ft_sprintf("%s/%s", path_array[idx], cmd);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(path_array[idx++]);
		free(exec_path);
	}
	free(path_array);
	return (NULL);
}
