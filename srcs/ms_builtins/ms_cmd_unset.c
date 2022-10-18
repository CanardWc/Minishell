#include <minishell.h>

static void	ms_free_node(t_list *node)
{
	t_env	*env;

	env = node->content;
	free(env->key);
	env->key = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
	env = NULL;
	node->next = NULL;
	free(node);
}

static t_list	*ms_replace_node(t_list *lst, t_list *node)
{
	t_list	*ret;

	ret = lst;
	if (lst == node)
		ret = ret->next;
	else
	{
		while (lst && lst->next)
		{
			if (lst->next == node)
			{
				lst->next = lst->next->next;
				return (ret);
			}
			lst = lst->next;
		}
	}
	return (ret);
}

static t_list	*ms_search_node(t_list *lst, char *str)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (!ft_strcmp(env->key, str))
			return (lst);
		lst = lst->next;
	}
	return (0);
}

void		ms_cmd_unset(t_data *data, char **line)
{
	t_list	*node;

	while (*++line)
	{
		node = ms_search_node(data->env, *line);
		if (node)
		{
			data->env = ms_replace_node(data->env, node);
			ms_free_node(node);
		}
		node = ms_search_node(data->var, *line);
		if (node)
		{
			data->var = ms_replace_node(data->var, node);
			ms_free_node(node);
		}
	}
	data->exit_status = 0;
}
