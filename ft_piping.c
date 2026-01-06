/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/06 21:04:45 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	ft_fork_create(t_pipe *head, int proc_nbr, pid_t pid);
static void	ft_setup_wait_order(t_pipe *head, pid_t pid, int proc_nbr);

int	ft_piping(char **argv, t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_free_chain(head), perror("pipe"), 1);
	pid = ft_fork_create(head, proc_nbr, 0);
	if (pid == -1)
		return (ft_free_chain(head), -1);
	if (pid != 0)
		waitpid(pid, NULL, 0);
	ft_exec_pipe_exit(head, pipefd, pid);
}

static pid_t	ft_fork_create(t_pipe *head, int proc_nbr, int *fd)
{
	int	i;
	int	pid;
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
	}
	return (pid);
}

ft_exec_pipe_exit(t_pipe *head, int *pipefd, int pid)
{
	t_pipe *node;

	node = head;
	if (pid == 0)
		close(pipefd[0]);
}
