/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/08 19:05:00 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe	*ft_new_node(char *cmd, char *exec_path, char * file, int pos);

t_pipe	*ft_parsing(char **argv, char **paths, int proc_nbr)
{
	int		i;
	char	*path;
	t_pipe	*head;
	t_pipe	*node;

	i = 1;
	path = ft_find_exec_path(argv[i], paths);
	head = ft_new_node(argv[i], path, argv[0], i);
	node = head;
	while (argv[++i] && i <= proc_nbr)
	{
		free(path);
		path = ft_find_exec_path(argv[i], paths);
		if (i < proc_nbr)
			node->next = ft_new_node(argv[i], path, NULL, i);
		else if (i == proc_nbr)
			node->next = ft_new_node(argv[i], path, argv[(proc_nbr + 1)], i);
		if (!node->next)
			return (ft_free_chain(head), NULL);
		node = node->next;
	}
	free(path);
	return (head);
}

static t_pipe	*ft_new_node(char *cmd, char *exec_path, char *file, int pos)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->exec_path = exec_path;
	if (file == NULL)
		node->file = ft_get_env_var(envp, "PWD=", 4);
	else
		node->file = file;
	node->pos = pos;
	node->mark = false;
	node->next = NULL;
	return (node);
}
