#include <minishell.h>

void	ms_cmd_cd(t_data *data, char **line)
{
	if (chdir(line[1]))
	{
		ft_printf("%s\n", strerror(errno));
		data->exit_status = errno;
	}
	else
		data->exit_status = 0;
}
