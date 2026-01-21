/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/21 17:16:27 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe	*chain_creation(char **argv);
static t_pipe	*new_node(char *input, int pos);
static char		*find_exec_pathname(char *arg, char *path_var);
static char		**organize_arguments(char **args);

t_pipe	*parsing(char **argv, char *path_var)
{
	t_pipe	*head;
	t_pipe	*node;
	char	**args;

	head = chain_creation(argv);
	node = head->next;
	while (node && node->next)
	{
		args = ft_split(node->input, ' ');
		node->pathname = find_exec_pathname(args[0], path_var);
		if (node->pathname)
			node->arguments = organize_arguments(args);
		if (!node->pathname)
			node->pathname = ft_strdup(args[0]);
		free_table(args);
		node = node->next;
	}
	return (head);
}

static t_pipe	*chain_creation(char **argv)
{
	t_pipe	*head;
	t_pipe	*node;
	int		i;

	i = 0;
	head = new_node(argv[i], i);
	node = head;
	while (argv[++i])
	{
		node->next = new_node(argv[i], i);
		if (!node->next)
			return (free_chain(head), NULL);
		node = node->next;
	}
	return (head);
}

static t_pipe	*new_node(char *input, int pos)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->input = input;
	node->pathname = NULL;
	node->arguments = NULL;
	node->pos = pos;
	node->next = NULL;
	return (node);
}

static char	*find_exec_pathname(char *arg, char *path_var)
{
	char	**paths;
	char	*name;
	char	*pathname;
	int		i;

	i = 0;
	if (arg[i] == '/' && access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	else if (arg[i] == '/' && access(arg, X_OK) == -1)
		return (NULL);
	name = ft_strjoin("/", arg);
	if (!name)
		return (NULL);
	paths = ft_split(path_var, ':');
	while (paths[i])
	{
		pathname = ft_strjoin(paths[i++], name);
		if (access(pathname, X_OK) == 0)
			return (free_table(paths), free(name), pathname);
		free(pathname);
	}
	return (free_table(paths), free(name), NULL);
}

static char	**organize_arguments(char **args)
{
	int		i;
	int		len;
	char	**result;

	i = 0;
	len = ft_doubleptr_len((const char **)args);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[len] = NULL;
	while (i < len)
	{
		result[i] = ft_strdup(args[i]);
		i++;
	}
	return (result);
}
