/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:57:42 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/11 19:32:50 by ssutarmi         ###   ########.fr       */
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
		return (ft_error_handler(argv[i]));
	i++;
	while (argv[i] && access(argv[i], F_OK) == 0)
	{
		proc_nbr++;
		exec_path = ft_find_exec_path(argv[i], paths);
		if (exec_path == NULL)
			ft_error_handler();
		free(exec_path);
		i++;
		while (argv[i] && access(argv[i], X_OK) == -1)
			i++;
	}
	return (proc_nbr);
}

static int	ft_error_handler(char *argument, char **envp)
{
	char	*shell;

	shell = ft_get_env_var(envp, "SHELL=", 6);
	if (errno = 2 && )
		ft_printf("%s: command not found: %s", shell, argument);
	argument = *envp;
	perror("this value means");
	return (-1);
}
