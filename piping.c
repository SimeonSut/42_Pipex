/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/28 19:25:43 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	forking(t_pipe *node, char **envp, int *pipe_fd);

int	piping(t_pipe *node, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_in;
	pid_t	pid_out;

	if (pipe(pipe_fd) == -1)
		return (perror(""), -1);
	pid_in = forking(node, envp, pipe_fd);
	if (pid_in == -1)
		return (-1);
	close(pipe_fd[1]);
	node = node->next->next;
	pid_out = forking(node, envp, pipe_fd);
	if (pid_out == -1)
		return (-1);
	close(pipe_fd[0]);
	if (waitpid(pid_in, NULL, 0) == -1)
		return (perror(""), -1);
	if (waitpid(pid_out, NULL, 0) == -1)
		return (perror(""), -1);
	return (0);
}

static pid_t	forking(t_pipe *node, char **envp, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		proc_one_split(node, envp, pipe_fd);
		return (-1);
	}
	return (pid);
}
