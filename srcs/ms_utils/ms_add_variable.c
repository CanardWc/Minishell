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

static void	ms_search_and_add(t_data *data)
{
	char	**src = NULL;
	char	*mark = NULL;
	char	*key = NULL;

	src = data->args->content;
	while (*src)
	{
		mark = ft_strchr(*src, '=');
		if (mark)
		{
			key = ft_substr(*src, 0, mark - *src);
			if (ms_lstsearch(data->env, key))
				ms_replace(ms_lstsearch(data->env, key), *src);
			else if (ms_lstsearch(data->var, key))
				ms_replace(ms_lstsearch(data->var, key), *src);
			else
				ft_lstadd_back(&data->var, \
						ft_lstnew(ms_new_var(*src)));
			free(key);
		}
		else
			return ;
		src++;
	}
}

void		ms_add_variable(t_data *data)
{
	t_list	*tmp;

	tmp = data->args;
	while (tmp)
	{
		if (**(char **)(tmp->content) == '|')
			return ;
		tmp = tmp->next;
	}
	ms_search_and_add(data);
	for (t_list *oui=data->var; oui; oui=oui->next)
	{
		t_env	*ah = oui->content;
		ft_printf("key = [%s] value = [%s]\n", ah->key, ah->value);
	}
}
