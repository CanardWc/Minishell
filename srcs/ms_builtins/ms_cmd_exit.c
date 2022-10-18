#include <minishell.h>

void	ms_cmd_exit(t_data *data, char **line)
{
	line = 0;
	ft_printf("exit\n");
	data->exit = 1;
}
