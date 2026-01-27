/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:01:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/27 20:30:56 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		here_doc_check(t_pipe *node);
static pid_t	forking(t_pipe *node, char **envp, int *pipe_fd);

int	piping(t_pipe *node, char **envp)
{
	int	pipe_in[2];
	int	pipe_out[2];

	if (pipe(pipe_fd) == -1)
		return (perror(""), -1);
	here_doc_check(node);
	if (forking(node, envp, pipe_in) == 0)
		return (-1);
	close(pipe_in[1]);
	node = node->next->next;
	while (node->next)
	{
		if (pipe(pipe_out) == -1)
			return (-1);
		if (forking(node, envp, pipe_in, pipe_out) == 0)
			return (-1);
		node = node->next;
	}
}

static void	here_doc_check(t_pipe *node)
{
	t_pipe	*track;

	if (strncmp(node->input, "here_doc", 9) != 0)
		return ;
	track = node;
	while (track)
	{
		track->here_doc = true;
		track = track->next;
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
	return (pid);
}

/*
int	piping(t_pipe *node, char **envp)
{
	int		pipe_in[2];
	int		pipe_out[2];

	if (pipe(pipe_in) == -1)
		return (perror(""), -1);
	if (pipe(pipe_out) == -1)
		return (perror(""), -1);
	here_doc_check(node);
	if (file_opener(node) == -1)
		return (perror(""), -1);
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
			return (perror(""), -1);
		close(pipe_out[0]);
		if (dup2(pipe_out[1], pipe_in[1]) == -1)
			return (perror(""), -1);
		close(pipe_out[1]);
		if (pipe(pipe_out) == -1)
			return (perror(""), -1);
		close(pipe_in[1]);
		node = node->next;
	}
	return (-1);
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
		return (perror(""), -1);
	return (pid);
}

static void	here_doc_check(t_pipe *node)
{
	t_pipe	*track;

	if (strncmp(node->input, "here_doc", 9) != 0)
		return ;
	track = node;
	while (track)
	{
		track->here_doc = true;
		track = track->next;
	}
}

static int	file_opener(t_pipe *node)
{
	t_pipe	*track;
	int		last_fd;

	track = node;
	while (track->next)
		track = track->next;
	if (track->here_doc == true)
		last_fd = open(track->input, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		last_fd = open(track->input, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (last_fd != -1)
		track->fd = last_fd;
	return (last_fd);
}*/
