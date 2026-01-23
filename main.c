/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/23 23:14:58 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static void	print_chain(t_pipe *head);

int	main(int argc, char **argv, char **envp)
{
	char	*path_var;
	t_pipe	*head;

	if (argc != 5)
		return (0);
	argv++;
	path_var = get_env_var(envp, "PATH=", 5);
	head = parsing(argv, path_var);
	if (!head)
		return (1);
	if (piping(head, envp) == -1)
		return (1);
	return (free_chain(head), 1);
}

/*static void	print_chain(t_pipe *head)
{
	int	i;

	while (head)
	{
		i = 0;
		ft_printf("pos %d input	is : %s\n", head->pos, head->input);
		ft_printf("pos %d pathname	is : %s\n", head->pos, head->pathname);
		if (head->arguments)
		{
			while (head->arguments[i])
			{
				ft_printf("pos %d arg %s\n", head->pos, head->arguments[i]);
				i++;
			}
		}
		head = head->next;
	}
}*/
