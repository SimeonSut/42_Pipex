/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/28 19:11:21 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	*path_var;
	t_pipe	*head;
	t_pipe	*node;

	if (argc != 5)
		return (0);
	argv++;
	path_var = get_env_var(envp, "PATH=", 5);
	head = parsing(argv, path_var);
	if (!head)
		return (1);
	node = head;
	if (piping(node, envp) == -1)
	{
		free_chain(head);
		exit(EXIT_FAILURE);
	}
	free_chain(head);
	return (0);
}
