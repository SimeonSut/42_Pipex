/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/02 17:26:53 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	ft_fork_creation(t_pipe *head, int proc_nbr, pid_t pid);
static void	ft_populate_struct_pid(t_pipe *head, pid_t pid, int len);
static void	ft_setup_wait_order(t_pipe *head, pid_t pid);

int	ft_piping(char **argv, t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_free_chain(head), perror("pipe"), 1);
	pid = ft_fork_creation(head, proc_nbr, 0);
	if (pid == -1)
		return (ft_free_chain(head), -1);
	ft_setup_wait_order(head, pid);
	ft_execve_and_pipe();
}

static pid_t	ft_fork_creation(t_pipe *head, int proc_nbr, pid_t pid)
{
	int	i;
	t_pipe	*node;

	i = 0;
	node = head;
	while (pid == 0 && proc_nbr > i)
	{
		pid = fork();
		if (pid == -1)
			return (ft_printf("iter %d", proc_nbr), perror(" fork"), -1);
		else if (pid == 0)
			ft_populate_struct_pid(node, pid, ++i);
		else
			ft_populate_struct_pid(node, pid, i);
	}
	return (pid);
}

static void	ft_populate_struct_pid(t_pipe *head, pid_t pid, int len)
{
	while (head->pos < len)
		head = head->next;
	head->pid = pid;
	return ;
}

static void	ft_setup_wait_order(t_pipe *head, pid_t pid)
{
	t_pipe	*node;

	node = head;
	while (node->next && node->pid != pid && node->next->pid != pid)
		node = node->next;
	if (!node->next)
	{
		ft_printf("UNEXPECTED EXIT: ft_setup_wait_order");
		return ;
	}
	if (node->next->pid == pid)
		waitpid(node->pid, NULL, 0);
	return ;
}

void	ft_execve_and_pipe(char **argv, t_pipe *head, pid_t pid)
{
	execve(head->path, )
}
