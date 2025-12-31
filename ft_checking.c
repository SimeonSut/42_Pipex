/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:57:42 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/31 19:09:09 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_check_args(char **argv, int len, char **paths)
{
	char	*exec_path;
	int		i;

	i = 0;
	if (access(argv[i++], F_OK) == 0)
		return (ft_free(paths), perror("access"), false);
	while (argv[i] && i < len)
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
}
