/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/12 17:32:48 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe	*ft_new_node(char *cmd, char *exec_path, char *file, int pos);
static char		**ft_get_cmd_args(char **argv, int pos);

t_pipe	*ft_parsing(int argc, char **argv, char **paths, int proc_nbr)
{
	int		i;
	char	*path;
	t_pipe	*head;
	t_pipe	*node;

	i = 1;
	path = ft_find_exec_path(argv[i], paths);
	head = ft_new_node(argv, path, argv[0], i++);
	node = head;
	while (argv[i] && --proc_nbr > 0)
	{
		while (access(argv[i], F_OK | R_OK | X_OK) == -1)
			i++;
		free(path);
		path = ft_find_exec_path(argv[i], paths);
		if (proc_nbr > 1)
			node->next = ft_new_node(argv, path, NULL, i++);
		else if (proc_nbr == 1)
			node->next = ft_new_node(argv, path, argv[(argc - 1)], i++);
		if (!node->next)
			return (free(path), ft_free_chain(head), NULL);
		node = node->next;
	}
	return (free(path), head);
}

static t_pipe	*ft_new_node(char **argv, char *exec_path, char *file, int pos)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->cmd_args = ft_get_cmd_args(argv, pos);
	node->exec_path = exec_path;
	node->file = file;
	node->pos = pos;
	node->mark = false;
	node->next = NULL;
	return (node);
}

static char	**ft_get_cmd_args(char **argv, int pos)
{
	int		i;
	int		j;
	char	**cmd_args;

	i = 0;
	j = 0;
	if (access(argv[pos], F_OK | R_OK | X_OK) == 0)
	{
		i++;
		while (access(argv[(pos + i)], X_OK) == -1)
			i++;
	}
	cmd_args = malloc((i + 1) * sizeof(char *));
	cmd_args[i] = "\0";
	while (j < i)
	{
		cmd_args[j] = argv[(pos + j)];
		j++;
	}
	return (cmd_args);
}
