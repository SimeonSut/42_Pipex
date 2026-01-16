/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/16 20:40:40 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	piping(t_pipe *head, char **argv)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close (pipefd[0]);
		dup2(pipefd[1], 1);
	}
}
