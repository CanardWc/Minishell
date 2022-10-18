#include <minishell.h>

const t_cmds	g_cmds[] = {
	{"echo", &ms_cmd_echo}, {"cd", &ms_cmd_cd}, \
	{"pwd", &ms_cmd_pwd}, {"export", &ms_cmd_export}, \
	{"unset", &ms_cmd_unset}, {"env", &ms_cmd_env}, \
	{"exit", &ms_cmd_exit}, {"exec", &ms_cmd_exec}};

static void	ms_set_redir(t_token token)
{
	if (token.red_in > 0)
	{
		dup2(token.red_in, 0);
		close(token.red_in);
	}
	if (token.red_out > 0)
	{
		dup2(token.red_out, 1);
		close(token.red_out);
	}
}

void		ms_find_cmd(t_data *data, t_token *token)
{
	int	status;
	pid_t	child;
	int	k;

	if (!token->cmds || !*(token->cmds) || !**(token->cmds))
		return ;
	k = 0;
	ms_set_redir(*token);
	while (k < 7 && ft_strcmp(g_cmds[k].string, token->cmds[0]))
		k++;
	if (k < 7)
		g_cmds[k].fct(data, token->cmds);
	else if (!data->pipe_count)
	{
		child = fork();
		if (child == 0)
		{
			g_cmds[7].fct(data, token->cmds);
			exit (data->exit_status);
		}
		waitpid(child, &status, 0);
		data->exit_status = WEXITSTATUS(status);
	}
	else
		g_cmds[7].fct(data, token->cmds);
}
