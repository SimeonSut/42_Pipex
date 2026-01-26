/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:47:21 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/26 20:07:09 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_doc_child(t_pipe *node, int *pipe_in);
static void	first_child(t_pipe *node, char **envp, int *pipe_in);
static void	mid_child(t_pipe *node, char **envp, int *pipe_in, int *pipe_out);
static void	last_child(t_pipe *node, char **envp, int *pipe_out);

int	proc_split(t_pipe *node, char **envp, int *pipe_in, int *pipe_out)
{
	if (node->pos == 0 && node->here_doc == true)
		here_doc_child(node, pipe_in);
	else if (node->pos == 0)
		first_child(node, envp, pipe_in);
	else if (node && node->next && node->next->next)
		mid_child(node, envp, pipe_in, pipe_out);
	else if (node && node->next && !node->next->next)
		last_child(node, envp, pipe_in);
	return (0);
}

static void	here_doc_child(t_pipe *node, int *pipe_in)
{
	char	*line;
	char	*limiter;
	int		lim_len;

	limiter = node->next->input;
	lim_len = ft_strlen(limiter);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (strncmp(line, limiter, lim_len) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_in[1]);
		free(line);
	}
	get_next_line(-1);
	return ;
}

static void	first_child(t_pipe *node, char **envp, int *pipe_in)
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
	dup2(pipe_in[1], STDOUT_FILENO);
	close(pipe_in[0]);
	close(pipe_in[1]);
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}

static void	mid_child(t_pipe *node, char **envp, int *pipe_in, int *pipe_out)
{
	dup2(pipe_in[0], STDIN_FILENO);
	close(pipe_in[0]);
	dup2(pipe_out[1], STDOUT_FILENO);
	close(pipe_out[1]);
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}

static void	last_child(t_pipe *node, char **envp, int *pipe_out)
{
	char	*output_file;
	int		fd;

	output_file = NULL;
	if (node->next)
	{
		output_file = node->next->input;
		fd = node->next->fd;
	}
	dup2(pipe_out[0], STDIN_FILENO);
	close(pipe_out[1]);
	close(pipe_out[0]);
	if (output_file)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (ft_strncmp(node->pathname, "", 1))
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}
