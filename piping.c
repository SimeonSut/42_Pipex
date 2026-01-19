/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/19 21:19:28 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	input_process(t_pipe *head, char **envp, int *pipefd);
static int	output_process(t_pipe *head, char **envp, int *pipefd);
static void	print_chain(t_pipe *head);

int	piping(t_pipe *head, char **envp)
{
	int		pipefd[2];
	pid_t	pid_in;
	pid_t	pid_out;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid_in = fork();
	if (pid_in == -1)
		return (perror("fork"), -1);
	if (pid_in == 0)
		input_process(head, envp, pipefd);
	if (waitpid(pid_in, NULL, 0) == -1)
		return (-1);
	pid_out = fork();
	if (pid_out != 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (pid_out == 0)
		output_process(head, envp, pipefd);
	if (waitpid(pid_out, NULL, 0) == -1)
		return (-1);
	return (0);
}

static void	input_process(t_pipe *head, char **envp, int *pipefd)
{
	t_pipe	*node;
	int		fd;
	char	*input_file;

	node = head;
	input_file = node->token;
	fd = open(node->token, O_RDWR);
	if (fd == -1)
		perror("input open");
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("input dup2");
	close(fd);
	while (!node->pathname)
		node = node->next;
	node->arguments = doubleptr_add(node->arguments, input_file, 1);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("2ndinput dup2");
	//close(pipefd[1]);
	//close(pipefd[0]);
	execve(node->pathname, node->arguments, envp);
	perror("execve input");
	exit(EXIT_FAILURE);
}

static int	output_process(t_pipe *head, char **envp, int *pipefd)
{
	t_pipe	*node;
	int		fd;

	node = head;
	while (node && node->next && node->next->next)
		node = node->next;
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("parent dup2");
	close(pipefd[0]);
	close(pipefd[1]);
	fd = open(node->next->token, O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror("parent open");
	//if (dup2(STDOUT_FILENO, fd) == -1)
	//	perror("parents dup2");
	print_chain(node);
	execve(node->pathname, node->arguments, envp);
	perror("execve parent");
	exit(EXIT_FAILURE);
}

static void	print_chain(t_pipe *head)
{
	int	i;

	i = 0;
	while (head)
	{
		ft_printf("pos %d token	is : %s\n", head->pos, head->token);
		ft_printf("pos %d pathname	is : %s\n", head->pos, head->pathname);
		if (head->arguments)
		{
			i = 0;
			while (head->arguments[i])
			{
				ft_printf("arg are %s\n", head->arguments[i]);
				i++;
			}
		}
		head = head->next;
	}
}
