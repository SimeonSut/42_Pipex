/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/16 16:09:43 by ssutarmi         ###   ########.fr       */
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
