/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/13 15:06:15 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	int		proc_nbr;
	t_pipe	*head;

	if (argc < 5)
		return (1);
	paths = ft_split(ft_get_env_var(envp, "PATH=", 5), ':');
	argv++;
	proc_nbr = ft_check_args(argv, paths);
	if (proc_nbr == -1)
		return (ft_free(paths), 1);
	head = ft_parsing(argc, argv, paths, proc_nbr);
	ft_free(paths);
	if (!head)
		return (1);
	if (ft_piping(argv, envp, head, proc_nbr) == -1)
		return (ft_free_chain(head), 1);
	return (ft_free_chain(head), 0);
}
