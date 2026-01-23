/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:01:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/23 23:12:58 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	mid_loop(t_pipe	*node, char **envp, int *pipe_in, int *pipe_out);

int	piping(t_pipe *node, char **envp)
{
	int		pipe_in[2];
	int		pipe_out[2];
	pid_t	pid;

	if (pipe(pipe_in) == -1)
		return (-1);
	if (pipe(pipe_out) == -1)
		return (-1);
	pid = fork();
	if (pid == 1)
		return (-1);
	if (pid == 0)
		proc_split(node, envp, pipe_in, pipe_out);
	if (waitpid(pid, NULL, 0) == -1)
		return (-1);
	close(pipe_in[1]);
	node = node->next->next;
	pid = mid_loop(node, envp, pipe_in, pipe_out);
	if (pid == -1)
		return (-1);
	if (pid == 0)
		proc_split(node, envp, pipe_in, pipe_out);
	return (0);
}

static pid_t	mid_loop(t_pipe	*node, char **envp, int *pipe_in, int *pipe_out)
{
	pid_t	pid;

	while (node && node->next)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			proc_split(node, envp, pipe_in, pipe_out);
		if (waitpid(pid, NULL, 0) == -1)
			return (-1);
		close(pipe_in[0]);
		if (!node->next->next)
		{
			close (pipe_out[1]);
			break ;
		}
		pipe_in = pipe_out;
		if (pipe(pipe_out) == -1)
			return (perror("pipe switch failure:"), -1);
		close(pipe_in[1]);
		node = node->next;
	}
	pid = fork();
	return (pid);
}
