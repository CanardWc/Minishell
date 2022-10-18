#include <minishell.h>

static int	ms_check_exist(char *line)
{
	int	ret;

	ret = 1;
	while (line && *line && !ft_strchr("\'\"= ", *line))
		line++;
	if (!*line || *line != '=')
		ret = 0;
	return (ret);
}

void		ms_flush_variables(t_token *token)
{
	char	**cmds;
	char	**new;
	int	l;

	l = 0;
	cmds = token->cmds;
	while (cmds && *cmds && ms_check_exist(*cmds))
		cmds++;
	if (cmds == token->cmds)
		return ;
	while (cmds[l])
		l++;
	new = (char **)malloc(sizeof(char *) * (l + 1));
	l = -1;
	while (cmds[++l])
		new[l] = ft_strdup(cmds[l]);
	new[l] = NULL;
	cmds = token->cmds;
	while (*cmds)
		free(*cmds++);
	free(token->cmds);
	token->cmds = new;
}
