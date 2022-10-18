#include <minishell.h>

void	ms_error(void)
{
	ft_printf("ms_error : %s\n", strerror(errno));
	exit(0);
}

static t_data	ms_init_data(char **env)
{
	t_data	data;

	data.pipe_count = 0;
	data.std_in = dup(0);
	data.std_out = dup(1);
	data.tokens = NULL;
	data.true_env = ft_split(getenv("PATH"), ':');
	data.env = ms_build_env(env);
	data.var = NULL;
	data.exit_status = 0;
	data.exit = 0;
	return (data);
}

static void	ms_refresh_values(t_data data)
{
	close(0);
	dup(data.std_in);
	close(1);
	dup(data.std_out);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;

	//if (ac != 1)
	//	return (0);
	//av = NULL;
	data = ms_init_data(env);
	data.ac = ac;
	if (ac > 1)
	{
		data.to_supr = av + 1;
	}
	else
		data.to_supr = NULL;
	//while (!data.exit)
	//{
		//ft_printf("minishell > ");
		ms_parsing(&data);
		if (data.tokens)
		{
			ms_logic(&data);
			ft_lstclear(&data.tokens, &ms_clear_node);
			data.tokens = NULL;
			ms_refresh_values(data);
		}
	//}
	//free $ variable;
	return (0);
}
