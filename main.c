/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/16 20:31:08 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_chain(t_pipe *head);

int	main(int argc, char **argv, char **envp)
{
	char 	*path_var;
	t_pipe	*head;

	path_var = get_env_var(envp, "PATH=", 5);
	argv++;
	head = parsing(argv, path_var);
	if (!head)
		return (1);
	print_chain(head);
	if (piping(head, argv) == -1)
		return (1);
	return (free_chain(head), argc);
}

static void	print_chain(t_pipe *head)
{
	while (head)
	{
		ft_printf("pos %d token	is : %s\n", head->pos, head->token);
		ft_printf("pos %d pathname	is : %s\n", head->pos, head->pathname);
		ft_printf("\n");
		head = head->next;
	}
}
