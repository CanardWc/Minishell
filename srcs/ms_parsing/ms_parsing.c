#include <minishell.h>

static void	ms_parse_error(t_data *data, int indic, void *to_free)
{
	to_free = 0;
	data = 0;
	if (indic == 0)
		printf("ms_error : %s\n", strerror(errno));
}

static void	ms_treat_piped(t_data *data, char **piped)
{
	t_token	*token;
	t_list	*node;

	while (*piped)
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (!token)
			return (ms_parse_error(data, 0, NULL));
		token->red_in = -2;
		token->red_out = -2;
		*piped = ms_redirections(*piped, token);
		if (!*piped)
			return (ms_parse_error(data, 0, token));
		token->cmds = ms_split(*piped);
		if (!token->cmds)
			return (ms_parse_error(data, 0, token));
		token->cmds = ms_replace_variables(data, token->cmds);
		if (!token->cmds)
			return (ms_parse_error(data, 0, token));
		ms_add_variables(data, token);
		if (ms_remove_quotes(token->cmds))
			return (ms_parse_error(data, 0, token));
		node = ft_lstnew(token);
		if (!node)
			return (ms_parse_error(data, 0, NULL));
		ft_lstadd_back(&data->tokens, node);
		piped++;
	}
}

void		ms_parsing(t_data *data)
{
	char	*line;
	char	**piped;
	char	**tmp;

	piped = NULL;
	//if (get_next_line(0, &line) < 0)
	//	return (ms_parse_error(data, 0, NULL));
	line = NULL;
	if (data->to_supr)
	{
		line = ft_strdup("");
	for (char **tmp = data->to_supr; data->ac > 1; tmp++)
	{
		line = strcat(line, " ");
		line = strcat(line, *tmp);
		data->ac--;
	}
	}
	if (!line)
		return ;
	if (*line)
		piped = ms_pipes(data, line);
	free(line);
	if  (!piped)
		return ;
	ms_treat_piped(data, piped);
	tmp = piped;
	while (*tmp)
		free(*tmp++);
	free(piped);
}
