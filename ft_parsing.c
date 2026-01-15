/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/15 19:07:25 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe	*ft_new_node(char **argv, char *exec_path, char *file, int i);
static char		**ft_get_cmd_args(char **argv, int i);
static void		ft_set_process_numbers(t_pipe *head);

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
		while (argv[i] && access(argv[i], X_OK) == -1)
			i++;
		free(path);
		path = ft_find_exec_path(argv[i], paths);
		if (argv[i] && proc_nbr > 1)
			node->next = ft_new_node(argv, path, NULL, i++);
		else if (argv[i] && proc_nbr == 1)
			node->next = ft_new_node(argv, path, argv[(argc - 1)], i++);
		if (argv[i] && !node->next)
			return (free(path), ft_free_chain(head), NULL);
		else if (node->next)
			node = node->next;
	}
	return (ft_set_process_numbers(head), free(path), head);
}

static t_pipe	*ft_new_node(char **argv, char *exec_path, char *file, int i)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->cmd_args = ft_get_cmd_args(argv, i);
	node->exec_path = exec_path;
	node->file = file;
	node->process = 0;
	node->mark = false;
	node->next = NULL;
	return (node);
}

static char	**ft_get_cmd_args(char **argv, int i)
{
	int		j;
	int		k;
	char	**cmd_args;

	j = 1;
	k = 0;
	if (access(argv[i + j], X_OK) == -1)
		while (argv[(i + j + 1)] && access(argv[(i + j)], X_OK) == -1)
			j++;
	cmd_args = malloc((j + 1) * sizeof(char *));
	cmd_args[j] = NULL;
	while (k < j)
	{
		cmd_args[k] = ft_strdup(argv[(i + k)]);
		k++;
	}
	return (cmd_args);
}

static void	ft_set_process_numbers(t_pipe *head)
{
	t_pipe	*node;
	int		process;

	node = head;
	process = 1;
	while (node)
	{
		node->process = process;
		process++;
		node = node->next;
	}
}
