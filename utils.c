/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/31 18:58:10 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_exec_path(char *command, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!command || !paths)
		return (NULL);
	command = ft_strjoin ("/", command);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], command);
		if (access(cmd_path, F_OK) == 0)
		{
			if ((access(cmd_path, R_OK) != 0) || (access(cmd_path, X_OK) != 0))
				return (free(command), ft_free(paths), perror("access"), NULL);
			else
				return (free(command), ft_free(paths), cmd_path);
		}
		free (cmd_path);
	}
	return (free(command), ft_free(paths), NULL);
}

char	*ft_get_env_var(char **envp, char *key, int check_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, check_len) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
