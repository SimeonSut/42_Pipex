
#include "Libft/libft.h"

typedef struct s_pipe_list
{
	char				*cmd;
	char				*exec_path;
	int					pos;
	int					pid;
	struct s_pipe_list	*next;
}	t_pipe;

//main.c//
int		main(int argc, char **argv, char **envp);

//ft_checking.c//
bool	ft_check_args(char **argv, int len, char **paths);

//ft_parsing.c//
void	ft_parsing(int argc, char **argv, char **paths);

//ft_piping.c//

//utils.c//
char	*ft_find_exec_path(char *command, char **paths);
char	*ft_get_env_var(char **envp, char *key, int check_len);

//cleaning.c//
void	ft_free(char **table);
void	ft_free_chain(t_pipe *head);
