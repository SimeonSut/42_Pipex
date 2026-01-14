/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:57:42 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/14 19:17:49 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_command_not_found(char *argument, char **envp);

int	ft_check_args(char **argv, char **paths, char **envp)
{
	int		i;
	int		proc_nbr;
	char	*exec_path;

	i = 0;
	proc_nbr = 0;
	if (access(argv[i], F_OK) == -1)
		return (ft_command_not_found(argv[i], envp), -1);
	i++;
	while (argv[i])
	{
		exec_path = ft_find_exec_path(argv[i], paths);
		if (!exec_path)
			return (ft_command_not_found(argv[i], envp), -1);
		while (argv[i])
		{
			free(exec_path);
			exec_path = ft_find_exec_path(argv[++i], paths);
			if (exec_path)
				break ;
		}
	}
	return (proc_nbr);
}

static void	ft_command_not_found(char *argument, char **envp)
{
	char	**shell_var;
	int		i;

	i = 0;
	shell_var = ft_split(ft_get_env_var(envp, "SHELL=", 6), '/');
	while (shell_var[i])
		i++;
	ft_putstr_fd(shell_var[--i], 2);
	ft_putstr_fd(": command not found: ", 2);
	ft_putstr_fd(argument, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
