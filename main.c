/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/15 16:34:44 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	*path_var;
	int		proc_nbr;
	t_pipe	*head;

	path_var = ft_get_env_var(envp, "PATH=", 5);
	paths = ft_split(path_var, ':');
	argv++;
	proc_nbr = ft_check_args(argv, paths, envp);
	if (proc_nbr == -1)
		return (free_table(paths), 1);
	head = ft_parsing(argc, argv, paths, proc_nbr);
	if (!head)
		return (1);
	free_table(paths);
	if (ft_piping(argv, envp, head, proc_nbr) == -1)
		return (ft_free_chain(head), 1);
	return (ft_free_chain(head), 0);
}
