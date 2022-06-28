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

static int	ms_search_and_add(t_data *data)
{
	char	**src;
	char	*mark;
	char	*key;

	src = data->args->content;
	while (*src)
	{
		mark = ft_strchr(*src, '=');
		if (**src != '\'' && **src != '\"' && mark)
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
			return (src - (char **)(data->args->content));
		src++;
	}
	return (src - (char **)(data->args->content));
}

void		ms_add_variable(t_data *data)
{
	t_list	*tmp;
	char	**src;
	int	ret;
	int	i;

	tmp = data->args;
	while (tmp)
	{
		if (**(char **)(tmp->content) == '|')
			return ;
		tmp = tmp->next;
	}
	ret = ms_search_and_add(data);
	i = 0;
	src = data->args->content;
	while (i < ret)
	{
	//	ft_printf("oui\n");
		free(src[i++]);
	}
	while (ret && src[i])
	{
	//	ft_printf("cooucou\n", ret);
		*src = src[i];
		src++;
	}
	if (ret)
		*src = 0;
	//ft_printf("ret = %d\n", ret);
	//ft_printf("len = %d\n", ft_strlen((char *)(data->args->content)));
	//for (t_list *oui=data->var; oui; oui=oui->next)
	//{
	//	t_env	*ah = oui->content;
	//	ft_printf("key = [%s] value = [%s]\n", ah->key, ah->value);
	//}
}
