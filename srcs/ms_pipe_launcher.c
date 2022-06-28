#include <minishell.h>

void	pipex_stdin(char **av, int **fd, int i)
{
	int	fd_start;

	fd_start = 0;
	if (i == 0)
	{
		fd_start = open(av[1], O_RDONLY);
		if (fd_start < 0)
			ms_error();
		dup2(fd_start, STDIN_FILENO);
		close(fd_start);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
	}
}

void	pipex_stdout(int pipe_count, char **av, int **fd, int i)
{
	int	fd_end;

	fd_end = 0;
	if (i == (ac - 4))
	{
		fd_end = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_end < 0)
			ms_error();
		dup2(fd_end, STDOUT_FILENO);
		close(fd_end);
		close(fd[i][0]);
	}
	else
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
	}
}

void	pipex_setup_child(int pipe_count, int ***fd, pid_t **child)
{
	int	i;

	*fd = (int **)malloc(sizeof(int *) * (pipe_count));
	if (*fd == NULL)
		ms_error();
	i = 0;
	while (i < pipe_count)
	{
		(*fd)[i] = (int *)malloc(sizeof(int) * 2);
		if ((*fd)[i++] == NULL)
			ms_error();
	}
	*child = (pid_t *)malloc(sizeof(pid_t) * (pipe_count - 3));
	if (*child == NULL)
		ms_error();
}

void	pipex_child(t_data data, char **path_env, int **fd, int i)
{
	char	*path;
	char	**cmd;
	int		j;

	cmd = ft_split(data.av[i + 2], ' ');
	pipex_stdin(data.av, fd, i);
	pipex_stdout(data.ac, data.av, fd, i);
	path = pipex_find_path(data.av[i + 2], path_env);
	if (path == NULL)
		ms_error();
	if (execve(path, cmd, path_env) == -1)
		ms_error();
	j = 0;
	while (cmd[j])
		free(cmd[j++]);
	free(cmd);
	cmd = NULL;
	free(path);
	path = NULL;
}

void	ms_pipe_launcher(t_data data, int pipe_count)
{
	pid_t	*child;
	int		**fd;
	int		status;
	int		i;

	child = NULL;
	fd = NULL;
	pipex_setup_child(pipe_count, &fd, &child);
	i = 0;
	while (i < pipe_count)
	{
		pipe(fd[i]);
		child[i] = fork();
		if (child[i] < 0)
			ms_error();
		else if (child[i] > 0)
			close(fd[i][1]);
		else
			pipex_child(data, path_env, fd, i);
		i++;
	}
	i = 0;
	while (i < (data.ac - 3))
		waitpid(child[i++], &status, 0);
	exit(0);
}
