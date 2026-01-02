/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/02 11:09:37 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe	*ft_new_node(char *cmd, char *exec_path, int pos, pid_t pid);

t_pipe	*ft_parsing(int argc, char **argv, char **paths, int len)
{
	int		i;
	char	*path;
	t_pipe	*head;
	t_pipe	*node;

	i = 1;
	path = ft_find_exec_path(argv[i], paths);
	head = ft_new_node(argv[i], path, i, -1);
	node = head;
	while (argv[++i] && i < len)
	{
		free(path);
		path = ft_find_exec_path(argv[i], paths);
		node->next = ft_new_node(argv[i], path, i, -1);
		if (!node->next)
			return (ft_free_chain(head), NULL);
		node = node->next;
	}
	return (head);
}

static t_pipe	*ft_new_node(char *cmd, char *exec_path, int pos, pid_t pid)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->exec_path = exec_path;
	node->pos = pos;
	node->pid = pid;
	node->next = NULL;
	return (node);
}
