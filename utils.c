/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/06 18:25:17 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_exec_path(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!cmd || !paths)
		return (NULL);
	if (access(cmd, F_OK) && access(cmd, R_OK) && access(cmd, W_OK))
		return (cmd);
	cmd = ft_strjoin ("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			if ((access(cmd_path, R_OK) != 0) || (access(cmd_path, X_OK) != 0))
				return (free(cmd), free(cmd_path), perror("access"), NULL);
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

void	ft_populate_struct_pid(t_pipe *head, pid_t pid, int i)
{
	t_pipe	*node;
	int		len;

	node = head;
	len = i + 1;
	while (node->pos != len)
		node = node->next;
	node->pid = pid;
	return ;
}
