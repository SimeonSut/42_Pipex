/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:26:26 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/31 20:42:33 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_piping(char *argv, t_pipe *head, int cmd_nbr)
{
	int	pid;
	int	nbr;
	int	pipe_fd[2];

	nbr = 0;
	if (pipe(pipe_fd) == -1)
		return (ft_free_chain(head), perror("pipe"), 1);
	while (nbr < (cmd_nbr + 1))
		pid = fork();
}
