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
	data.true_env = ft_split(getenv("PATH"), ':');
	data.env = ms_build_env(env);
	data.var = NULL;
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
			for (t_list *tmp = data.args; tmp; tmp = tmp->next)
			{
				ft_printf("node\n");
				char **tmp2 = (char **)tmp->content;
				for (int i = 0; tmp2[i]; i++)
					ft_printf("arg[%d] = |%s|\n", i, tmp2[i]);
			}
			if (!ms_treat_line(&data))
			{
				ms_add_variable(&data);
				ms_exec_line(&data);
			}
			ft_lstclear(&data.args, &ms_clear_node);
			data.args = NULL;
		}
	}
	//free $ variable;
	return (0);
}
