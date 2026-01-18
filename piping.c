/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/18 19:36:46 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(t_pipe *head, char **argv, char **envp, int *pipefd);
static void	parent_process(t_pipe *head, char **argv, char **envp, int *pipefd);

int	piping(t_pipe *head, char **argv, char **envp)
{
	int		pipefd[2];
	char	**args;
	t_pipe	*node;
	pid_t	pid;

	node = head;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		child_process(head, argv, envp, pipefd);
	else if (pid != 0)
	{
		if (waitpid(pid, NULL, 0) == -1)
			perror("waitpid");
		parent_process(head, argv, envp, pipefd);
	}
	return (0);
}

static void	child_process(t_pipe *head, char **argv, char **envp, int *pipefd)
{
	t_pipe	*node;
	int		fd;
	int		new_fd;
	int		pipe_w;

	node = head;
	fd = open(node->token, O_RDWR);
	if (fd == -1)
		perror("child open");
	new_fd = dup2(fd, 0);
	if (new_fd == -1)
		perror("child dup2");
	close(fd);
	while (!node->pathname)
		node = node->next;
	pipe_w = dup2(pipefd[1], 1);
	if (pipe_w == -1)
		perror("2ndchild dup2");
	close(pipefd[0]);
	close(pipefd[1]);
	execve(node->pathname, node->arguments, envp);
	perror("execve child");
	exit(EXIT_FAILURE);
}

static void	parent_process(t_pipe *head, char **argv, char **envp, int *pipefd)
{
	t_pipe	*node;
	int		fd;
	int		pipe_r;
	int		outfile;

	node = head;
	while (node && node->next && node->next->next)
		node = node->next;
	pipe_r = dup2(pipefd[0], 0);
	if (pipe_r == -1)
		perror("parent dup2");
	close(pipefd[0]);
	close(pipefd[1]);
	fd = open(node->next->token, O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror("parent open");
	outfile = dup2(fd, 1);
	if (outfile == -1)
		perror("parent 2nddup2");
	close(fd);
	execve(node->pathname, node->arguments, envp);
	perror("execve parent");
	exit(EXIT_FAILURE);
}
