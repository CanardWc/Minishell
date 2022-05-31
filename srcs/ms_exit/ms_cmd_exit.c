#include <minishell.h>

void	ms_cmd_exit(t_data *data, char **line)
{
	line = 0;
	if (ft_strcmp("exit", *((char **)(data->args->content))))
		return ;
	ft_printf("exit\n");
	data->exit = 1;
}
