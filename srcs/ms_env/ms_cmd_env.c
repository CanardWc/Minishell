#include <minishell.h>

void	ms_cmd_env(t_data *data, char **line)
{
	t_list	*tmp;
	t_env	*ret;

	tmp = data->env;
	if (*++line)
		ft_printf("env command can't take options or arguments\n");
	else
		while (tmp)
		{
			ret = tmp->content;
			ft_printf("%s=%s\n", ret->key, ret->value);
			tmp=tmp->next;
		}
	data = 0;
}
