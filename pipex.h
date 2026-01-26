/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:28:48 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/26 19:08:15 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipe_list
{
	char				*input;
	char				*pathname;
	char				**arguments;
	int					pos;
	int					fd;
	bool				here_doc;
	struct s_pipe_list	*next;
}	t_pipe;

// PARSING.C
t_pipe	*parsing(char **argv, char *path_var);

// UTILS.C
char	*get_env_var(char **envp, char *keyword, int check_len);
void	execve_error_message(char **envp, char *cmd);
void	input_error_message(t_pipe *node, char *input, char **envp);

// CLEANING.C
void	free_chain(t_pipe *head);
t_pipe	*free_node(t_pipe *node);

// PIPING.C
int		piping(t_pipe *node, char **envp);

// PIPING_BONUS.C
int		piping(t_pipe *node, char **envp);

// CHILDREN_BONUS.C
int		proc_split(t_pipe *node, char **envp, int *pipe_in, int *pipe_out);

#endif
