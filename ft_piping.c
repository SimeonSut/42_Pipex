/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/08 19:17:25 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	ft_forking(t_pipe *head, int proc_nbr, pid_t pid);
static void		ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid);

int	ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_free_chain(head), perror("pipe"), 1);
	pid = ft_forking(head, proc_nbr, 0);
	if (pid == -1)
		return (ft_free_chain(head), -1);
	if (pid != 0)
		waitpid(pid, NULL, 0);
	ft_pipeset(head, envp, pipefd, pid);
	return (true);
}

static pid_t	ft_forking(t_pipe *head, char **argv, int proc_nbr, pid_t pid)
{
	int		i;
	pid_t	pid;
	t_pipe	*node;

	i = 0;
	node = head;
	while (pid == 0 && proc_nbr > i)
	{
		pid = fork();
		if (pid < 0)
			return (ft_printf("iter %d", proc_nbr), perror(" fork"), -1);
		else if (pid == 0)
			i++;
		while (node->next && (i + 1) != node->pos)
			node = node->next;
		node->mark = true;
	}
	return (pid);
}

static void	ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid)
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
		exit();
}
