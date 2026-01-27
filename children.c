/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:53:57 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/27 19:33:18 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		first_child(t_pipe *node, char **envp, int *pipe_in);
static void		last_child(t_pipe *node, char **envp, int *pipe_out);

int	proc_one_split(t_pipe *node, char **envp, int *pipe_fd)
{
	if (node->pos == 0)
		first_child(node, envp, pipe_fd);
	else if (node && node->next && !node->next->next)
		last_child(node, envp, pipe_fd);
	return (0);
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
	close(pipe_in[1]);
	if (ft_strncmp(node->pathname, "", 1) != 0)
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}

static void	last_child(t_pipe *node, char **envp, int *pipe_out)
{
	char	*output_file;
	int		fd;

	output_file = NULL;
	if (node->next)
		output_file = node->next->input;
	dup2(pipe_out[0], STDIN_FILENO);
	close(pipe_out[0]);
	if (output_file)
	{
		fd = open(output_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return ;
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (ft_strncmp(node->pathname, "", 1) != 0)
		execve(node->pathname, node->arguments, envp);
	execve_error_message(envp, node->pathname);
}
