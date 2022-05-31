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

static void	ms_args(t_data *data, char **line)
{
	t_list	*tmp;
	t_list	*rpl;

	tmp = data->var;
	rpl = NULL;
	while (tmp && *line)
	{
		if (ft_strcmp(((t_env *)(tmp->content))->key, *line))
		{
			ft_lstadd_back(&data->env, tmp);
			if (tmp == data->var)
				data->var = NULL;
			else
			{
				rpl = data->var;
				while (rpl->next != tmp)
					rpl = rpl->next;
				rpl->next = tmp->next;
			}
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
}
