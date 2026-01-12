/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/12 13:55:53 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_exec_path(char *cmd, char **paths)
{
	char	*cmd_path;
	char	*cmdn;
	int		i;

	i = 0;
	if (!cmd || !paths)
		return (NULL);
	cmdn = ft_strjoin ("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], cmdn);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, R_OK | X_OK) != 0)
				return (free(cmdn), free(cmd_path), perror("access"), NULL);
			else
				return (free(cmdn), cmd_path);
		}
		free (cmd_path);
	}
	return (free(cmdn), cmd);
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
