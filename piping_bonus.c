/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:01:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/29 15:52:41 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		here_doc_check(t_pipe *node);
static pid_t	forking(t_pipe *node, char **envp, int *pipe_fd, int fd_in);
static int		close_and_wait(int *pipe_fd, int fd_in);

int	piping(t_pipe *node, char **envp)
{
	int	pipe_fd[2];
	int	fd_in;
	int	wstatus;

	fd_in = 0;
	if (pipe(pipe_fd) == -1)
		return (perror(""), -1);
	here_doc_check(node);
	while (node->next)
	{
		if (forking(node, envp, pipe_fd, fd_in) == -1)
			return (-1);
		fd_in = pipe_fd[0];
		if (close(pipe_fd[1]) == -1)
			return (perror(""), -1);
		if (pipe(pipe_fd) == -1)
			return (-1);
		if (node->pos == 0)
			node = node->next->next;
		else
			node = node->next;
	}
	wstatus = close_and_wait(pipe_fd, fd_in);
	return (wstatus);
}

static void	here_doc_check(t_pipe *node)
{
	t_pipe	*track;

	if (ft_strncmp(node->input, "here_doc", 9) != 0)
		return ;
	track = node;
	while (track)
	{
		track->here_doc = true;
		track = track->next;
	}
}

static pid_t	forking(t_pipe *node, char **envp, int *pipe_fd, int fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (node->pos == 0 && node->here_doc == true)
		if (pid != 0)
			if (waitpid(pid, NULL, 0) == -1)
				return (perror(""), -1);
	if (pid == 0)
	{
		if (proc_split(node, envp, pipe_fd, fd_in) == 0)
			return (-1);
	}
	if (fd_in != 0)
		if (close(fd_in) == -1)
			return (perror(""), -1);
	return (pid);
}

static int	close_and_wait(int *pipe_fd, int fd_in)
{
	int	wstatus;

	if (close(pipe_fd[0]) == -1)
		return (perror(""), -1);
	if (close(pipe_fd[1]) == -1)
		return (perror(""), -1);
	if (close(fd_in) == -1)
		return (perror(""), -1);
	wait(&wstatus);
	while (WIFEXITED(wstatus) == true)
	{
		if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
			return (-1);
		else
		{
			if (wait(&wstatus) == -1)
				break ;
		}
	}
	return (wstatus);
}
