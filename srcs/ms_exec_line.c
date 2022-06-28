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
		child = fork();
		if (child == 0)
			g_cmds[7].fct(data, line);
		waitpid(child, &status, 0);
	}
}

void	ms_exec_line(t_data *data)
{
	t_list	*tmp;

	tmp = data->args;
	//if (tmp.pipes)
	//	ms_pipe_launcher(tmp);
	while (tmp)
	{
		ms_find_cmd(data, tmp->content);
		tmp = tmp->next;
	}
}
