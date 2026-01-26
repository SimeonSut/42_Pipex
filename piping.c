/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/26 19:08:25 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	input_process(t_pipe *node, char **envp, int *pipefd);
static int	output_process(t_pipe *node, char **envp, int *pipefd);
static int	file_opener(t_pipe *node);

int	piping(t_pipe *node, char **envp)
{
	int		pipefd[2];
	pid_t	pid_in;

	if (pipe(pipefd) == -1 || file_opener(node) == -1)
		return (perror(""), -1);
	pid_in = fork();
	if (pid_in == -1)
		return (perror(""), -1);
	if (pid_in == 0)
		if (input_process(node, envp, pipefd) == -1)
			return (-1);
	if (waitpid(pid_in, NULL, 0) == -1)
		return (perror(""), -1);
	node = node->next->next;
	pid_in = fork();
	if (pid_in == -1)
		return (perror(""), -1);
	close(pipefd[1]);
	if (pid_in == 0)
		if (output_process(node, envp, pipefd) == -1)
			return (-1);
	if (waitpid(pid_in, NULL, 0) == -1)
		return (perror(""), -1);
	return (0);
}

static int	input_process(t_pipe *node, char **envp, int *pipefd)
{
	int		fd;
	char	*input_file;

	input_file = node->input;
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		input_error_message(node, input_file, envp);
	while (node && node->pos != 1)
		node = node->next;
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
	return (-1);
}

static int	output_process(t_pipe *node, char **envp, int *pipefd)
{
	char	*output_file;
	int		fd;

	output_file = NULL;
	if (node->next)
	{
		output_file = node->next->input;
		fd = node->next->fd;
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	if (output_file)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
	return (-1);
}

static int	file_opener(t_pipe *node)
{
	t_pipe	*track;
	int		last_fd;

	track = node;
	while (track->next)
		track = track->next;
	last_fd = open(track->input, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (last_fd != -1)
		track->fd = last_fd;
	return (last_fd);
}
