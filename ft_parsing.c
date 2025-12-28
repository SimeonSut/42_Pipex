/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:31:04 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/28 19:33:25 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_exec_path(char *command, char **paths);

void	ft_parsing(int argc, char **argv, char **envp)
{
	char	*paths;
	char	*cmd_path;
	char	*cmd_arg;

	paths = ft_get_env_var(envp, "PATH=");
	cmd_path = ft_exec_path(argv[2], ft_split(paths, ':'));
	if (!cmd_path)
		return ;
	if (execve(cmd_path, &argv[1], envp) == -1)
		perror("execve");
	return ;
}

static char	*ft_exec_path(char *command, char **paths)
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
