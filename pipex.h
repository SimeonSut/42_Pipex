/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:28:48 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/06 20:57:01 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <sys/wait.h>

typedef struct s_pipe_list
{
	char				*cmd;
	char				*exec_path;
	int					pos;
	struct s_pipe_list	*next;
}	t_pipe;

//main.c//
int		main(int argc, char **argv, char **envp);

//ft_checking.c//
bool	ft_check_args(char **argv, int len, char **paths);

//ft_parsing.c//
t_pipe	*ft_parsing(int argc, char **argv, char **paths, int len);

//ft_piping.c//
int		ft_piping(char **argv, t_pipe *head, int proc_nbr);

//utils.c//
char	*ft_find_exec_path(char *command, char **paths);
char	*ft_get_env_var(char **envp, char *keyword, int check_len);
void	ft_populate_struct_pid(t_pipe *head, pid_t pid, int i);

//cleaning.c//
void	ft_free(char **table);
void	ft_free_chain(t_pipe *head);

#endif