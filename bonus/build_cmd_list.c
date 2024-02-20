/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:13:14 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/20 03:05:03 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_cmdnew(void *content)
{
	t_cmd	*new_l;

	new_l = malloc(sizeof(struct s_list));
	if (!new_l)
		return (NULL);
	new_l->content = ft_strdup(content);
	new_l->next = NULL;
	return (new_l);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	ft_cmditer(t_cmd *lst, void (*f)(char **))
{
	t_cmd	*curr;

	if (!lst)
		return ;
	while (lst)
	{
		curr = lst;
		lst = curr->next;
		f(&curr->content);
	}
}

void	cleanup_struct(t_pipe *pipe)
{
	t_cmd *tmp;

	while (pipe->cmd_head)
	{
		tmp = pipe->cmd_head;
		pipe->cmd_head = pipe->cmd_head->next;
		free(tmp->content);
		free(tmp);
	}
	free(pipe);
}
