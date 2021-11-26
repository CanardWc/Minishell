#include <minishell.h>

void	ms_error(void)
{
	ft_printf("ms_error : %s\n", strerror(errno));
	exit(0);
}

t_data	ms_init_data(char **env)
{
	t_data	data;

	data.args = NULL;
	data.env = env;
	data.exit = 0;
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (0);
	av = NULL;
	data = ms_init_data(env);
	while (!data.exit)
	{
		ft_printf("minishell > ");
		ms_parse(&data);
		if (data.args)
		{
			for (int i = 0; data.args[i]; i++)
			{
				printf("arg[%d] = %s\n", i, data.args[i]);
				free(data.args[i]);
			}
			free(data.args);
			data.args = NULL;
		}
		//ms_treat_line(&data);
		//ms_exec_line(&data);
		//free(data.args);
	}
	return (0);
}
