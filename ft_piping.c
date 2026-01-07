/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/07 19:22:20 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	ft_fork_create(t_pipe *head, int proc_nbr, pid_t pid);
static void	ft_exec_pipe(t_pipe *head, char **envp, int *pipefd, int pid);

int	ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr)
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
	ft_exec_pipe(head, envp, pipefd, pid);
	return (true);
}

static pid_t	ft_fork_create(t_pipe *head, int proc_nbr, pid_t pid)
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
	}
	return (pid);
}

static void	ft_exec_pipe(t_pipe *head, char **envp, int *pipefd, int pid)
{
	t_pipe	*node;
	char	*pwd_env_variable;
	int		check;
	int		fd;

	node = head;
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(node->exec_path, node->cmd, envp);
	}
	else
	{
		pwd_env_variable = ft_get_env_var(envp, "PWD=", 4);
		fd = open(pwd_env_variable, O_CLOEXEC);
		dup2(pipefd[1], fd);
		dup2(pipefd[1], 1);
	}
}
// line 62: after the dup2 of pid == 0, do i need to close the write fd of the pipe or not?