#include <minishell.h>

void	ms_cmd_echo(t_data *data, char **line)
{
	int	tnl;

	tnl = 0;
	line++;
	if (!*line || !**line)
		ft_printf("\n");
	else
	{
		if (!ft_strncmp(*line, "-n", ft_strlen(*line)))
			tnl = 1;
		if (tnl)
			line++;
		while (*line)
		{
			if (*(line + 1))
				ft_printf("%s ", *line++);
			else
				ft_printf("%s", *line++);
		}
		if (!tnl)
			ft_printf("\n");
	}
	data->exit_status = 0;
}
