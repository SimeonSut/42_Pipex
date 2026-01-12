/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/12 19:33:53 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	ft_forking(t_pipe *head, int proc_nbr);
static void		ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid);

int	ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	int		pipefd[2];
	int		wstatus;
	t_pipe	*node;

	wstatus = 0;
	if (pipe(pipefd) == -1)
		return (ft_free_chain(head), perror("pipe"), 1);
	pid = ft_forking(head, proc_nbr);
	if (pid == -1)
		return (ft_free_chain(head), -1);
	if (pid != 0)
		waitpid(pid, &wstatus, 0);
	if (wstatus == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	node = ft_pipeset(head, envp, pipefd, pid);
	if (!node)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (execve(node->exec_path, node->cmd_args, envp) == -1)
		exit(EXIT_FAILURE);
	return (true);
}

static pid_t	ft_forking(t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	t_pipe	*node;

	node = head;
	pid = 0;
	while (pid == 0 && proc_nbr > 0)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			proc_nbr--;
		while (node->next && proc_nbr != node->pos)
			node = node->next;
		node->mark = true;
	}
	return (pid);
}

static t_pipe	ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid)
{
	t_pipe	*node;
	int		fd;

	node = head;
	while (node && node->mark != true)
		node = node->next;
	if (pid == 0)
		dup2(pipefd[1], 1);
	else if (pid != 0 && node->next)
	{
		fd = open(node->file, O_CLOEXEC);
		dup2(fd, pipefd[0]);
		dup2(pipefd[1], 1);
	}
	else if (pid != 0 && !node->next)
	{
		fd = open(node->file, O_RDWR);
		dup2(fd, 1);
		dup2(0, pipefd[0]);
	}
	if (fd == -1)
		return (NULL);
	return (node);
}
