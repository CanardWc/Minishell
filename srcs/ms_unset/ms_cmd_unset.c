#include <minishell.h>

static void	ms_free_node(t_list *node)
{
}

static int	ms_check_lst(t_list **lst, char *str)
{
	t_list	*tmp;
	t_env	*env;
	int	ret;

	tmp = lst;
	ret = 0;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, str))
		{
			if (tmp = lst && !tmp->next)
				ret = 3;
			else if (tmp = lst)
				ret = 2;
			else
			{
				while (lst->next != tmp)
					lst = lst->next;
				lst->next = tmp->next;
				ret = 1;
			}
			ms_free_node(tmp)
		}
		else
			tmp = tmp->next;
	}
	return (ret);
}

void		ms_cmd_unset(t_data *data, char **line)
{
	t_list	*tmp_env;
	t_list	*tmp_var;
	int	ret;

	tmp_env = data->env;
	tmp_var = data->var;
	while (*line)
	{
		ret = ms_check_lst(&data->env, *line);
		if (ret == 3)
			data->env = NULL;
		else if (ret == 2)
			data->env = data->env->next;
		ret = ms_check_lst(data->var, *line);
		if (ret == 3)
			data->var = NULL;
		else if (ret == 2)
			data->var = data->var->next;
		line++;	
	}
}
