#include <minishell.h>

const t_cmds	g_cmds[] = {
	{"echo", &ms_cmd_echo}, {"cd", &ms_cmd_cd}, \
	{"pwd", &ms_cmd_pwd}, {"export", &ms_cmd_export}, \
	{"unset", &ms_cmd_unset}, {"env", &ms_cmd_env}, \
	{"exit", &ms_cmd_exit}, {"exec", &ms_cmd_exec}};

void	ms_find_cmd(t_data *data, char **line)
{
	int	status;
	pid_t	child;
	int	k;

	k = 0;
	while (k < 7 && ft_strncmp(g_cmds[k].string, line[0], \
				ft_strlen(line[0])))
		k++;
	if (k < 7)
		g_cmds[k].fct(data, line);
	else
	{
		if (!data.pipes)
		{
			child = fork();
			if (child == 0)
				g_cmds[7].fct(data, line);
			waitpid(child, &status, 0);
		}
		else
			g_cmds[7].fct(data, line);
	}
}

void	ms_exec_line(t_data *data)
{
	t_list	*tmp;
	int		pipe_count;

	tmp = data->args;
	pipe_count = 0;
	while (tmp)
	{
		if (**(tmp->content) == '|')
			pipe_count++;
		tmp = tmp->next;
	}
	tmp = data->args;
	if (pipe_count)
		ms_pipe_launcher(data, pipe_counti + 1);
	else
	{
		while (tmp)
		{
			ms_find_cmd(data, tmp->content);
			tmp = tmp->next;
		}
	}
}
