/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/18 18:05:04 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_chain(t_pipe *head);

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
	if (piping(head, argv, envp) == -1)
		return (1);
	return (free_chain(head), argc);
}
/*
static void	print_chain(t_pipe *head)
{
	int	i;

	i = 0;
	while (head)
	{
		ft_printf("pos %d token	is : %s\n", head->pos, head->token);
		ft_printf("pos %d pathname	is : %s\n", head->pos, head->pathname);
		if (head->arguments)
		{
			i = 0;
			while (head->arguments[i])
			{
				ft_printf("arg are %s\n", head->arguments[i]);
				i++;
			}
		}
		head = head->next;
	}
}*/
