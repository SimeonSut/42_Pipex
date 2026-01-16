/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:28:48 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/16 20:30:27 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <sys/wait.h>

typedef struct s_pipe_list
{
	char				*token;
	char				*pathname;
	int					pos;
	struct s_pipe_list	*next;
}	t_pipe;

t_pipe	*parsing(char **argv, char *path_var);

char	*get_env_var(char **envp, char *keyword, int check_len);

void	free_chain(t_pipe *head);

int piping(t_pipe *head, char **argv);

#endif