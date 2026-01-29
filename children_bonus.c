/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:47:21 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/29 15:22:40 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_doc_child(t_pipe *node, int *pipe_fd);
static void	first_child(t_pipe *node, char **envp, int *pipe_fd);
static void	mid_child(t_pipe *node, char **envp, int *pipe_fd, int fd_in);
static void	last_child(t_pipe *node, char **envp, int fd_in);

int	proc_split(t_pipe *node, char **envp, int *pipe_fd, int fd_in)
{
	if (node->pos == 0 && node->here_doc == true)
		here_doc_child(node, pipe_fd);
	else if (node->pos == 0)
		first_child(node, envp, pipe_fd);
	else if (node && node->next && node->next->next)
		mid_child(node, envp, pipe_fd, fd_in);
	else if (node && node->next && !node->next->next)
		last_child(node, envp, fd_in);
	return (0);
}

static void	here_doc_child(t_pipe *node, int *pipe_fd)
{
	char	*line;
	char	*limiter;

	limiter = node->next->input;
	limiter = ft_strjoin(limiter, "\n");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(limiter);
	free_chain(node);
	exit(EXIT_SUCCESS);
}

static void	first_child(t_pipe *node, char **envp, int *pipe_fd)
{
	int		fd;
	char	*input_file;

	input_file = node->input;
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		input_error_message(node, input_file, envp);
	while (node && node->pos != 1)
		node = node->next;
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	if (close(fd) == -1)
		return ;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return ;
	if (close(pipe_fd[0]) == -1)
		return ;
	if (close(pipe_fd[1]) == -1)
		return ;
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}

static void	mid_child(t_pipe *node, char **envp, int *pipe_fd, int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return ;
	if (close(fd_in) == -1)
		return ;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return ;
	if (close(pipe_fd[1]) == -1)
		return ;
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}

static void	last_child(t_pipe *node, char **envp, int fd_in)
{
	char	*output_file;
	int		fd;

	output_file = node->next->input;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return ;
	if (close(fd_in) == -1)
		return ;
	if (node->here_doc == true)
		fd = open(output_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(output_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
		return ;
	if (close(fd) == -1)
		return ;
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}
