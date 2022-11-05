/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:21:41 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:27:37 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_error(void)
{
	printf("ms_error : %s\n", strerror(errno));
	exit(0);
}

static t_data	ms_init_data(char **env)
{
	t_data				data;
	struct sigaction	s_action;

	data.pipe_count = 0;
	data.std_in = dup(0);
	data.std_out = dup(1);
	data.tokens = NULL;
	data.true_env = ft_split(getenv("PATH"), ':');
	data.env = ms_build_env(env);
	data.var = NULL;
	data.exit_status = 0;
	data.exit = 0;
	s_action.sa_handler = ms_signal_handler;
	s_action.sa_mask = 0;
	s_action.sa_flags = 0;
	sigaction(SIGQUIT, &s_action, NULL);
	sigaction(SIGINT, &s_action, NULL);
	return (data);
}

static void	ms_refresh_values(t_data data)
{
	close(0);
	dup(data.std_in);
	close(1);
	dup(data.std_out);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (0);
	av = NULL;
	g_position_handler = MAIN;
	data = ms_init_data(env);
	while (!data.exit)
	{
		if (ms_parsing(&data))
			break ;
		if (data.tokens)
		{
			ms_logic(&data);
			ft_lstclear(&data.tokens, &ms_clear_node);
			data.tokens = NULL;
			ms_refresh_values(data);
		}
	}
	return (data.exit_status);
}
