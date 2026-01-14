/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/14 19:09:53 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_exec_path(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd[i] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	cmd = ft_strjoin ("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, R_OK | X_OK) != 0)
				return (free(cmd), free(cmd_path), NULL);
			else
				return (free(cmd), cmd_path);
		}
		free (cmd_path);
	}
	return (free(cmd), NULL);
}

char	*ft_get_env_var(char **envp, char *keyword, int check_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], keyword, check_len) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
