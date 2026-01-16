/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_model.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:16:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/16 14:18:52 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*ft_find_exec_path(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!cmd || cmd[i] == '/')
	{
		if (cmd && access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	cmd = ft_strjoin ("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) != 0)
				return (free(cmd_path), NULL);
			else
				return (cmd_path);
		}
		free (cmd_path);
	}
	return (NULL);
}
int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	*path_var;
	int		proc_nbr;
	t_pipe	*head;

	path_var = ft_get_env_var(envp, "PATH=", 5);
	paths = ft_split(path_var, ':');
	argv++;
	proc_nbr = ft_check_args(argv, paths, envp);
	if (proc_nbr == -1)
		return (free_table(paths), 1);
	head = ft_parsing(argc, argv, paths, proc_nbr);
	if (!head)
		return (1);
	free_table(paths);
	if (ft_piping(argv, envp, head, proc_nbr) == -1)
		return (ft_free_chain(head), 1);
	return (ft_free_chain(head), 0);
}

//checking.c

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
		if (!exec_path && argv[(i + 1)])
			return (ft_command_not_found(argv[i], envp), -1);
		proc_nbr++;
		free(exec_path);
		while (argv[++i])
		{
			exec_path = ft_find_exec_path(argv[i], paths);
			if (exec_path)
				break ;
		}
		free(exec_path);
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
	free_table(shell_var);
	return ;
}

// parsing.c

static t_pipe	*ft_new_node(char **argv, char *exec_path, char *file, int i);
static char		**ft_get_cmd_args(char **argv, int i);
static void		ft_set_process_numbers(t_pipe *head);

t_pipe	*ft_parsing(int argc, char **argv, char **paths, int proc_nbr)
{
	int		i;
	char	*path;
	t_pipe	*head;
	t_pipe	*node;

	i = 1;
	path = ft_find_exec_path(argv[i], paths);
	head = ft_new_node(argv, path, argv[0], i++);
	node = head;
	while (argv[i] && --proc_nbr > 0)
	{
		while (argv[i] && access(argv[i], X_OK) == -1)
			i++;
		free(path);
		path = ft_find_exec_path(argv[i], paths);
		if (argv[i] && proc_nbr > 1)
			node->next = ft_new_node(argv, path, NULL, i++);
		else if (argv[i] && proc_nbr == 1)
			node->next = ft_new_node(argv, path, argv[(argc - 1)], i++);
		if (argv[i] && !node->next)
			return (free(path), ft_free_chain(head), NULL);
		else if (node->next)
			node = node->next;
	}
	return (ft_set_process_numbers(head), free(path), head);
}

static t_pipe	*ft_new_node(char **argv, char *exec_path, char *file, int i)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->cmd_args = ft_get_cmd_args(argv, i);
	node->exec_path = exec_path;
	node->file = file;
	node->process = 0;
	node->mark = false;
	node->next = NULL;
	return (node);
}

static char	**ft_get_cmd_args(char **argv, int i)
{
	int		j;
	int		k;
	char	**cmd_args;

	j = 1;
	k = 0;
	if (access(argv[i + j], X_OK) == -1)
		while (argv[(i + j + 1)] && access(argv[(i + j)], X_OK) == -1)
			j++;
	cmd_args = malloc((j + 1) * sizeof(char *));
	cmd_args[j] = NULL;
	while (k < j)
	{
		cmd_args[k] = ft_strdup(argv[(i + k)]);
		k++;
	}
	return (cmd_args);
}

static void	ft_set_process_numbers(t_pipe *head)
{
	t_pipe	*node;
	int		process;

	node = head;
	process = 1;
	while (node)
	{
		node->process = process;
		process++;
		node = node->next;
	}
}

// piping.c

static pid_t	ft_forking(t_pipe *head, int proc_nbr);
static int		ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid);
static int		ft_execve(t_pipe *head, char **envp, int *pipefd, int file_fd);
static void		print_struct(t_pipe *head);

int	ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	int		pipefd[2];
	int		wstatus;
	int		file_fd;

	wstatus = 0;
	print_struct(head);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = ft_forking(head, proc_nbr);
	if (pid == -1)
		return (-1);
	if (pid != 0)
		waitpid(pid, &wstatus, 0);
	if (wstatus == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	file_fd = ft_pipeset(head, envp, pipefd, pid);
	if (file_fd == -1)
		return (-1);
	ft_execve(head, envp, pipefd, file_fd);
	return (true);
}

static pid_t	ft_forking(t_pipe *head, int proc_nbr)
{
	pid_t	pid;
	t_pipe	*node;

	node = head;
	pid = 0;
	while (pid == 0 && proc_nbr > 1)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		else if (pid == 0)
			proc_nbr--;
		while (node->next && proc_nbr != node->process)
			node = node->next;
		node->mark = true;
	}
	return (pid);
}

static int	ft_pipeset(t_pipe *head, char **envp, int *pipefd, int pid)
{
	t_pipe	*node;
	int		fd;

	node = head;
	while (node && node->mark != true)
		node = node->next;
	if (pid == 0)
	{
		fd = open(node->file, O_RDONLY);
		dup2(pipefd[1], 1);
	}
	else if (pid != 0 && node->next)
	{
		dup2(0, pipefd[0]);
		dup2(pipefd[1], 1);
		fd = 0;
	}
	else if (pid != 0 && !node->next)
	{
		fd = open(node->file, O_CREAT | O_WRONLY | O_TRUNC);
		dup2(fd, 1);
		dup2(0, pipefd[0]);
	}
	return (fd);
}

static int	ft_execve(t_pipe *head, char **envp, int *pipefd, int file_fd)
{
	t_pipe	*node;
	char	**tot_cmd_args;
	int		len;
	int		check;

	node = head;
	while (node && node->mark != true)
		node = node->next;
	if (!node->next)
	{
		check = close(pipefd[0]);
		node->cmd_args = doubleptr_add(node->cmd_args, node->file, 1);
	}
	else if (node->process == 1)
		check = close(pipefd[1]);
	if (check == -1)
		return (perror("close"), -1);
	if (execve(node->exec_path, node->cmd_args, envp) == -1)
		return (perror("execve"), -1);
	return (0);
}

// header


typedef struct s_pipe_list
{
	char				**cmd_args;
	char				*exec_path;
	char				*file;
	int					process;
	bool				mark;
	struct s_pipe_list	*next;
}	t_pipe;

//main.c//
int		main(int argc, char **argv, char **envp);

//ft_checking.c//
int		ft_check_args(char **argv, char **paths, char **envp);

//ft_parsing.c//
t_pipe	*ft_parsing(int argc, char **argv, char **paths, int proc_nbr);

//ft_piping.c//
int		ft_piping(char **argv, char **envp, t_pipe *head, int proc_nbr);

//utils.c//
char	*ft_find_exec_path(char *cmd, char **paths);
char	*ft_get_env_var(char **envp, char *keyword, int check_len);

//cleaning.c//
void	ft_free_chain(t_pipe *head);

// cleaning.c

void	ft_free_chain(t_pipe *head)
{
	t_pipe	*track;

	while (head)
	{
		track = head->next;
		free_table(head->cmd_args);
		free(head);
		head = track;
	}
	return ;
}