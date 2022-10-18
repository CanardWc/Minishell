#include <minishell.h>

static char	*ms_find_path(char *av, char **true_env)
{
	char	*tmp;
	char	*tmp2;

	if (av && *av != '/')
	{
		while (*true_env)
		{
			tmp = ft_strjoin(*true_env++, "/");
			if (tmp == NULL)
				ms_error();
			tmp2 = ft_strjoin(tmp, av);
			free(tmp);
			tmp = NULL;
			if (tmp2 == NULL)
				ms_error();
			if (!access(tmp2, F_OK))
				return (tmp2);
			free(tmp2);
			tmp2 = NULL;
		}
	}
	else if (!access(av, F_OK))
		return (av);
	return (NULL);
}

void	ms_cmd_exec(t_data *data, char **line)
{
	char	*path;

	path = ms_find_path(*line, data->true_env);
	if (path == NULL)
	{
		ft_printf("minishell: %s: command not found\n", *line);
		return ;
	}
	else if (execve(path, line, data->true_env) == -1)
		ms_error();
	free(path);
}
