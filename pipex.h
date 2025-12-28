
#include "Libft/libft.h"

typedef struct s_pipe_list
{
	char				*cmd;
	char				*exec_path;
	int					pos;
	struct s_pipe_list	*next;
}	t_pipe;

//main.c//
int		main(int argc, char **argv, char **envp);
char	*ft_get_env_var(char **envp, char *key);

//ft_parsing.c//
void	ft_parsing(int argc, char **argv, char **envp);

//cleaning.c//
void	ft_free(char **table);
