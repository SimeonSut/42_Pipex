/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:57:42 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/12 15:28:59 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_error_handler(char *argument, char **envp);

int	ft_check_args(char **argv, char **paths)
{
	int		i;
	int		proc_nbr;
	char	*exec_path;

	i = 0;
	proc_nbr = 0;
	if (access(argv[i], F_OK) == -1)
		return (ft_error_handler(argv[i]), envp);
	i++;
	while (argv[i] && access(argv[i], F_OK) == 0)
	{
		proc_nbr++;
		exec_path = ft_find_exec_path(argv[i], paths);
		if (exec_path == NULL)
			return (free(exec_path), -1);
		free(exec_path);
		i++;
		while (argv[i] && access(argv[i], X_OK) == -1)
			i++;
	}
	if (argv[i])
		ft_command_not_found(argv[i], envp);
	return (proc_nbr);
}

static void	ft_command_not_found(char *argument, char **envp)
{
	char	*shell;

	shell = ft_get_env_var(envp, "SHELL=", 6);
	ft_putstr_fd(shell, 2);
	ft_putstr_fd(": command not found: ", 2);
	ft_putstr_fd(argument);
	ft_putchar_fd('\n', 2);
	exit(127);
}
