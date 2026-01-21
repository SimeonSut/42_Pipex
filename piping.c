/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/21 17:22:20 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	input_process(t_pipe *head, char **envp, int *pipefd);
static void	output_process(t_pipe *head, char **envp, int *pipefd);

int	piping(t_pipe *head, char **envp)
{
	int		pipefd[2];
	pid_t	pid_in;
	pid_t	pid_out;

	if (pipe(pipefd) == -1)
		return (perror(""), -1);
	pid_in = fork();
	if (pid_in == -1)
		return (perror(""), -1);
	if (pid_in == 0)
		input_process(head, envp, pipefd);
	if (waitpid(pid_in, NULL, 0) == -1)
		return (perror(""), -1);
	pid_out = fork();
	if (pid_out != 0)
		close(pipefd[1]);
	if (pid_out == 0)
		output_process(head, envp, pipefd);
	if (waitpid(pid_out, NULL, 0) == -1)
		return (perror(""), -1);
	return (0);
}

static void	input_process(t_pipe *head, char **envp, int *pipefd)
{
	t_pipe	*node;
	int		fd;
	char	*input_file;

	node = head;
	input_file = node->input;
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		perror("");
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("");
	while (node && node->pos != 1)
		node = node->next;
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("");
	execve(node->pathname, node->arguments, envp);
	execve_error_message(head, envp, node->pathname);
}

static void	output_process(t_pipe *head, char **envp, int *pipefd)
{
	t_pipe	*node;
	char	*output_file;
	int		fd;

	node = head;
	while (node && node->pos != 2)
		node = node->next;
	output_file = node->next->input;
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("");
	close(pipefd[1]);
	close(pipefd[0]);
	fd = open(output_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		perror("");
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("");
	close(fd);
	execve(node->pathname, node->arguments, envp);
	execve_error_message(head, envp, node->pathname);
}
