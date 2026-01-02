/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:57:42 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/02 20:00:52 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_args(char **argv, char **paths)
{
	int		i;
	int		proc_nbr;
	char	*exec_path;

	i = 0;
	proc_nbr = 0;
	if (access(argv[i++], F_OK) == 0)
		return (ft_free(paths), perror("access"), false);
	while (argv[i] && access(argv[i], F_OK) == 0)
	{
		proc_nbr++;
		exec_path = ft_find_exec_path(argv[i], paths);
		if (exec_path == NULL)
			return (ft_free(paths), -1);
		free(exec_path);
		i++;
		while (argv[i] && access(argv[i], F_OK) == -1)
			i++;
	}
	return (proc_nbr);
}

/*
bool	ft_check_args(char **argv, int len, char **paths)
{
	int		i;
	char	*exec_path;

	i = 0;
	if (access(argv[i++], F_OK) == 0)
		return (ft_free(paths), perror("access"), false);
	while (argv[i] && i <= len)
	{
		exec_path = ft_find_exec_path(argv[i], paths);
		if (exec_path == NULL)
			return (ft_free(paths), false);
		else
		{
			free(exec_path);
			i++;
		}
	}
	return (true);
}*/
