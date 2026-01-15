/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/15 19:14:08 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	ft_forking(t_pipe *head, int proc_nbr);
static int		ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid);
static int		ft_execve(t_pipe *head, char **envp, int *pipefd, int file_fd);
static void		print_struct(t_pipe *head);

int	ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	int		pipefd[2];
	int		wstatus;
	int		file_fd;

	wstatus = 0;
	print_struct(head);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = ft_forking(head, proc_nbr);
	if (pid == -1)
		return (-1);
	if (pid != 0)
		waitpid(pid, &wstatus, 0);
	if (wstatus == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	file_fd = ft_pipeset(head, envp, pipefd, pid);
	if (file_fd == -1)
		return (-1);
	ft_execve(head, envp, pipefd, file_fd);
	return (true);
}

static pid_t	ft_forking(t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	t_pipe	*node;

	node = head;
	pid = 0;
	while (pid == 0 && proc_nbr > 1)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		else if (pid == 0)
			proc_nbr--;
		while (node->next && proc_nbr != node->process)
			node = node->next;
		node->mark = true;
	}
	return (pid);
}

static int	ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid)
{
	t_pipe	*node;
	int		fd;

	node = head;
	while (node && node->mark != true)
		node = node->next;
	if (pid == 0)
	{
		fd = open(node->file, O_RDONLY);
		dup2(pipefd[1], 1);
	}
	else if (pid != 0 && node->next)
	{
		dup2(0, pipefd[0]);
		dup2(pipefd[1], 1);
		fd = 0;
	}
	else if (pid != 0 && !node->next)
	{
		fd = open(node->file, O_CREAT | O_WRONLY | O_TRUNC);
		dup2(fd, 1);
		dup2(0, pipefd[0]);
	}
	return (fd);
}

static int	ft_execve(t_pipe *head, char **envp, int *pipefd, int file_fd)
{
	t_pipe	*node;
	char	**tot_cmd_args;
	int		len;
	int		check;

	node = head;
	while (node && node->mark != true)
		node = node->next;
	if (!node->next)
	{
		check = close(pipefd[0]);
		node->cmd_args = doubleptr_add(node->cmd_args, node->file, 1);
	}
	else if (node->process == 1)
		check = close(pipefd[1]);
	if (check == -1)
		return (perror("close"), -1);
	if (execve(node->exec_path, node->cmd_args, envp) == -1)
		return (perror("execve"), -1);
	return (0);
}

static void	print_struct(t_pipe *head)
{
	t_pipe	*node;
	int		i;

	node = head;
	while (node)
	{
		i = 0;
		while (node->cmd_args[i])
		{
			ft_printf("for the process %d, arg is : %s\n", node->process, node->cmd_args[i++]);
			ft_printf("exec_path is : %s\n", node->exec_path);
		}
			
		node = node->next;
	}
}
