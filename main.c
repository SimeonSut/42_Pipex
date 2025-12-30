/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/30 15:44:06 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (0);
	argv++;
	if (ft_check_args(argv, ft_doubleptr_len(argv), envp) == false)
		return (0);
	return (0);
}

bool	ft_check_args(char **argv, int len, char **paths)
{
	char	*exec_path;
	int		i;

	i = 0;
	if (ft_is_file(argv[++i]) == false)
		return (false);
	while (argv[i] && i < (len - 1))
	{
		exec_path = ft_exec_path(argv[i], paths);
		if (exec_path == NULL)
			return (false);
		else
		{
			free(exec_path);
			i++;
		}
	}
	if (ft_is_file(argv[i]) == false)
		return (false);
	return (true);
}
