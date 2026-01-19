/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/19 20:28:57 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char 	*path_var;
	t_pipe	*head;

	if (argc <= 4)
		return (0);
	path_var = get_env_var(envp, "PATH=", 5);
	argv++;
	head = parsing(argv, path_var);
	if (!head)
		return (1);
	if (piping(head, envp) == -1)
		return (free_chain(head), 1);
	return (free_chain(head), argc);
}
