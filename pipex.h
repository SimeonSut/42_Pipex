/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:28:48 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/12 16:56:36 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <sys/wait.h>

typedef struct s_pipe_list
{
	char				**cmd_args;
	char				*exec_path;
	char				*file;
	int					pos;
	bool				mark;
	struct s_pipe_list	*next;
}	t_pipe;

//main.c//
int		main(int argc, char **argv, char **envp);

//ft_checking.c//
bool	ft_check_args(char **argv, int len, char **paths);

//ft_parsing.c//
t_pipe	*ft_parsing(char **argv, char **paths, int proc_nbr);

//ft_piping.c//
int		ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr);

//utils.c//
char	*ft_find_exec_path(char *command, char **paths);
char	*ft_get_env_var(char **envp, char *keyword, int check_len);

//cleaning.c//
void	ft_free(char **table);
void	ft_free_chain(t_pipe *head);

#endif