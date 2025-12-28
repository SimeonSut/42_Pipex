/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/28 19:18:00 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	ft_parsing(argc, argv, envp);
	return (0);
}

bool	ft_file_check(char **envp, char *filename)
{
	char	*file_path;

	file_path = ft_get_env_var(envp, "PWD");
	return (true);
}

char	*ft_get_env_var(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
