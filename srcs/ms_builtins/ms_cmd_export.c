#include <minishell.h>

static void	ms_no_args(t_data *data)
{
	t_list	*tmp;
	t_env	*env;

	tmp = data->env;
	while (tmp)
	{
		env = tmp->content;
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		tmp = tmp->next;
	}
}

static t_list	*ms_replace(t_list *lst, t_list *node)
{
	t_list	*tmp;

	tmp = lst;
	if (lst == node)
		lst = lst->next;
	else
	{
		while (tmp && tmp->next)
		{
			if (tmp->next == node)
				tmp->next = tmp->next->next;
			tmp = tmp->next;
		}
	}
	node->next = NULL;
	return (lst);
}

static void	ms_args(t_data *data, char **line)
{
	t_list	*tmp;
	t_env	*env;

	tmp = data->var;
	while (tmp && *line)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, *line))
		{
			ft_lstadd_back(&data->env, tmp);
			data->var = ms_replace(data->var, tmp);
			tmp = data->var;
			line++;
		}
		else
			tmp = tmp->next;
	}
}

void	ms_cmd_export(t_data *data, char **line)
{
	if (!line[1])
		ms_no_args(data);
	else
		ms_args(data, ++line);
	data->exit_status = 0;
}
