/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:01:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/22 21:31:59 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	proc_split(t_pipe *head, t_pipe *node, char **envp, int *pipefd);
static void	first_child(t_pipe *head, t_pipe *node, char **envp, int *pipefd);
static void	mid_child(t_pipe *head, t_pipe *node, char **envp, int *pipefd);
static void	last_child(t_pipe *head, t_pipe *node, char **envp, int *pipefd);

int	piping(t_pipe *head, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	t_pipe	*node;

	node = head;
	while (node && node->next)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			proc_split(head, node, envp, pipefd);
		if (waitpid(pid, NULL, 0) == -1)
			return (-1);
		close (pipefd[1]);
		if (node && node->next && node->next->next && node->pos == 0)
			node = node->next->next;
		else
			node = node->next;
	}
	return (0);
}

static void	proc_split(t_pipe *head, t_pipe *node, char **envp, int *pipefd)
{
	if (node->pos == 0)
		first_child(head, node, envp, pipefd);
	else if (node && node->next && node->next->next)
		mid_child(head, node, envp, pipefd);
	else if (node && node->next && !node->next->next)
		last_child(head, node, envp, pipefd);
}

static void	first_child(t_pipe *head, t_pipe *node, char **envp, int *pipefd)
{
	int		fd;
	char	*input_file;

	input_file = node->input;
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		perror("1");
	while (node && node->pos != 1)
		node = node->next;
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("1");
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("1");
	close(pipefd[0]);
	close(pipefd[1]);
	execve(node->pathname, node->arguments, envp);
	execve_error_message(head, envp, node->pathname);
}

static void	mid_child(t_pipe *head, t_pipe *node, char **envp, int *pipefd)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("2 pipefd[0]");
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("2 pipefd[1]");
	close(pipefd[1]);
	execve(node->pathname, node->arguments, envp);
	execve_error_message(head, envp, node->pathname);
}

static void	last_child(t_pipe *head, t_pipe *node, char **envp, int *pipefd)
{
	char	*output_file;
	int		fd;

	output_file = NULL;
	if (node->next)
		output_file = node->next->input;
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("3");
	close(pipefd[1]);
	close(pipefd[0]);
	if (output_file)
	{
		fd = open(output_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd == -1)
			perror("3");
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("3");
		close(fd);
	}
	execve(node->pathname, node->arguments, envp);
	execve_error_message(head, envp, node->pathname);
}
