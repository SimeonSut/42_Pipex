/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_model.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:16:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/20 16:59:04 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parsing.c

static t_pipe	*chain_creation(char **argv);
static t_pipe	*new_node(char *token, int pos);
static char		*find_exec_pathname(char *arg, char *path_var);
static void		chain_args_addition(t_pipe *node, int count);

t_pipe	*parsing(char **argv, char *path_var)
{
	t_pipe	*head;
	t_pipe	*node;
	int		count;

	head = chain_creation(argv);
	if (!head)
		return (NULL);
	node = head;
	while (node)
	{
		if (node->pos != 0 || !node->next)
		{
			if (node->token[0] != '-')
				node->pathname = find_exec_pathname(node->token, path_var);
		}
		node = node->next;
	}
	node = head;
	count = 1;
	chain_args_addition(node, count);
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

static t_pipe	*new_node(char *token, int pos)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->token = token;
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
		if (access(pathname, F_OK) == 0)
			if (access(pathname, X_OK) == 0)
				return (free_table(paths), free(name), pathname);
		free(pathname);
	}
	return (free_table(paths), free(name), NULL);
}

static void	chain_args_addition(t_pipe *node, int count)
{
	char	**args;

	while (node->next && !node->pathname)
		node = node->next;
	node->pos = count;
	args = NULL;
	if (node && node->next && node->next->next && !node->next->pathname)
	{
		args = combine_ptr(2, node->pathname, node->next->token);
		node->next = free_node(node->next);
	}
	while (node && node->next && node->next->next && !node->next->pathname)
	{
		args = doubleptr_add(args, node->next->token, 1);
		node->next = free_node(node->next);
	}
	if (args)
		node->arguments = args;
	if (node && node->next && node->next->pathname && node->next->next)
		chain_args_addition(node->next, ++count);
	node->next->pos = node->pos + 1;
}
