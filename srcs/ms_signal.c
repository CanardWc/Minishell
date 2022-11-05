/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:22:14 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:22:10 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_signal_handler(int signal)
{
	if (signal == SIGINT && g_position_handler == MAIN)
		exit(1);
	if (signal == SIGINT && g_position_handler != FORK)
		write(1, "\n", 1);
	if (signal == SIGINT && (g_position_handler == READLINE
			|| g_position_handler == SIGNAL_ALARM))
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_position_handler = SIGNAL_ALARM;
	}
	if (signal == SIGQUIT && g_position_handler == EXECVE)
		ft_putstr_fd("Quit: 3\n", 2);
}
