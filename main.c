/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/07 14:22:22 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*head;
	int		proc_nbr;
	char	**paths;

	if (argc < 5)
		return (1);
	paths = ft_split(ft_get_env_var(envp, "PATH=", 5), ':');
	argv++;
	proc_nbr = ft_check_args(argv, proc_nbr, paths);
	if (proc_nbr == -1)
		return (1);
	head = ft_parsing(argc, argv, paths, proc_nbr);
	if (!head)
		return (1);
	if (ft_piping(argv, envp, head, proc_nbr) == false)
	return (0);
}
