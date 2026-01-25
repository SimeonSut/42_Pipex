/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/25 20:33:01 by ssutarmi         ###   ########.fr       */
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

void	execve_error_message(t_pipe *head, char **envp, char *cmd)
{
	char	**shell;
	char	*message;
	int		i;

	i = 0;
	message = strerror(errno);
	shell = ft_split(get_env_var(envp, "SHELL=", 6), '/');
	while (shell[i])
		i++;
	ft_putstr_fd(shell[--i], STDERR_FILENO);
	if (access(cmd, X_OK) == -1 && cmd[0] != '\0' && cmd[0] != '/')
		ft_putstr_fd(": command not found: ", STDERR_FILENO);
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		if (cmd[0] != '\0' && cmd[0] != '/')
			ft_putstr_fd(message, STDERR_FILENO);
		else
			ft_putstr_fd("Permission denied", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	free_table(shell);
}

void	input_error_message(char	*input, char **envp)
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
	ft_printf("%s: %s: %s\n", shell[i], message, input);
	free_table(shell);
	exit(EXIT_FAILURE);
}
