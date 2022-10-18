#include <minishell.h>

static t_env	*ms_new_var(char *src)
{
	t_env	*new;
	char	*mark;
	
	mark = ft_strchr(src, '=');
	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_substr(src, 0, mark - src);
		new->value = ft_strdup(mark + 1);
	return (new);
}

static void	ms_replace(t_env *env, char *src)
{
	char	*mark;

	mark = ft_strchr(src, '=');
	free(env->value);
		env->value = ft_strdup(mark + 1);
}

static t_env	*ms_lstsearch(t_list *lst, char *name)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (!ft_strcmp(name, env->key))
			return (env);
		lst = lst->next;
	}
	return (NULL);
}

static void	ms_adding(t_data *data, char **cmds)
{
	char	*line;
	char	*key;

	while (*cmds)
	{
		line = ft_strchr(*cmds, '=');
		key = ft_substr(*cmds, 0, line - *cmds);
		if (!ft_strcmp(key, "?") || !ft_strcmp(key, "$"))
		{
			free(key);
			return ;
		}
		if (ms_lstsearch(data->env, key))
			ms_replace(ms_lstsearch(data->env, key), *cmds);
		else if (ms_lstsearch(data->var, key))
			ms_replace(ms_lstsearch(data->var, key), *cmds);
		else
			ft_lstadd_back(&data->var, \
					ft_lstnew(ms_new_var(*cmds)));
		free(key);
		cmds++;
	}
}
					     
void		ms_add_variables(t_data *data, t_token *token)
{
	char	**cmds;
	char	*line;
	int	check;

	check = 0;
	cmds = token->cmds;
	while (*cmds && !check)
	{
		line = *cmds;
		while (*line && !ft_strchr("\"\'= ", *line))
			line++;
		if (!*line || *line != '=')
			check = 1;
		cmds++;
	}
	cmds = token->cmds;
	if (!check && !data->pipe_count)
		ms_adding(data, cmds);
	ms_flush_variables(token);
}
