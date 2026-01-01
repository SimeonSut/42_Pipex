/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/01 19:14:00 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	ft_fork_creation(t_pipe *head, int proc_nbr, int pid);
static void	ft_populate_struct_pid(t_pipe *head, int pid, int len);

int	ft_piping(char **argv, t_pipe *head, int proc_nbr)
{
	int	pid;
	int	nbr;
	int	pipe_fd[2];

	nbr = 0;
	if (pipe(pipe_fd) == -1)
		return (ft_free_chain(head), perror("pipe"), 1);
	if (ft_fork_creation(head, proc_nbr, 0) == false)
		return (-1);

}

static bool	ft_fork_creation(t_pipe *head, int proc_nbr, int pid)
{
	int	i;
	t_pipe	*node;

	i = 0;
	node = head;
	while (pid == 0 && proc_nbr > i)
	{
		pid = fork();
		if (pid == -1)
			return (ft_printf("iter %d", proc_nbr), perror(" fork"), false);
		else if (pid == 0)
			ft_populate_struct_pid(node, pid, ++i);
		else
			ft_populate_struct_pid(node, pid, i);
	}
	return (true);
}

static void	ft_populate_struct_pid(t_pipe *head, int pid, int len)
{
	while (head->pos < len)
		head = head->next;
	head->pid = pid;
}
