/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:01:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/25 20:51:32 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int		loop(t_pipe	*node, char **envp, int *pipe_in, int *pipe_out);
static pid_t	forking(t_pipe *node, char **envp, int *pipe_in, int *pipe_out);

int	piping(t_pipe *node, char **envp)
{
	int		pipe_in[2];
	int		pipe_out[2];

	if (pipe(pipe_in) == -1)
		return (-1);
	if (pipe(pipe_out) == -1)
		return (-1);
	if (forking(node, envp, pipe_in, pipe_out) == 0)
		return (0);
	close(pipe_in[1]);
	node = node->next->next;
	if (loop(node, envp, pipe_in, pipe_out) == 0)
		return (0);
	close(pipe_in[0]);
	close(pipe_out[1]);
	close(pipe_out[0]);
	return (0);
}

static int	loop(t_pipe	*node, char **envp, int *pipe_in, int *pipe_out)
{
	while (node && node->next)
	{
		if (forking(node, envp, pipe_in, pipe_out) == 0)
			return (0);
		if (!node->next->next)
			return (-1);
		close(pipe_in[0]);
		if (dup2(pipe_out[0], pipe_in[0]) == -1)
			return (-1);
		close(pipe_out[0]);
		if (dup2(pipe_out[1], pipe_in[1]) == -1)
			return (-1);
		close(pipe_out[1]);
		if (pipe(pipe_out) == -1)
			perror("pipe switch failure:");
		close(pipe_in[1]);
		node = node->next;
	}
}

static pid_t	forking(t_pipe *node, char **envp, int *pipe_in, int *pipe_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		if (proc_split(node, envp, pipe_in, pipe_out) == 0)
			return (0);
	if (waitpid(pid, NULL, 0) == -1)
		return (-1);
	return (pid);
}
