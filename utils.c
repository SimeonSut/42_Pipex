/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/22 21:31:46 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_var(char **envp, char *keyword, int check_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], keyword, check_len) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	execve_error_message(t_pipe *head, char **envp, char *pathname)
{
	char	**shell;
	int		i;

	i = 0;
	shell = ft_split(get_env_var(envp, "SHELL=", 6), '/');
	while (shell[i])
		i++;
	i--;
	if (access(pathname, X_OK) == -1)
	{
		ft_putstr_fd(shell[i], STDERR_FILENO);
		ft_putstr_fd(": command not found: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
	}
	else
		perror("");
	free_table(shell);
	free_chain(head);
	exit(EXIT_FAILURE);
}

void	main_error_message(char	*input, char **envp)
{
	char	**shell;
	char	*message;
	int		i;

	i = 0;
	message = strerror(errno);
	shell = ft_split(get_env_var(envp, "SHELL=", 6), '/');
	while (shell[i])
		i++;
	i--;
	ft_printf("%s: %s: %s", shell[i], message, input);
	free_table(shell);
	exit(EXIT_FAILURE);
}

void	pipe_switch(int *pipefd)
{
	int	new_pipefd[2];

	if (pipe(new_pipefd) == -1)
		perror("pipe_switch");
	if (dup2(new_pipefd[1], pipefd[0]) == -1)
		return ;
	close(new_pipefd[1]);
	*pipefd = *new_pipefd;
}
