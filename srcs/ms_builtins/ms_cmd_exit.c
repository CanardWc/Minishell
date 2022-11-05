/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:54:49 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:12:21 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_cmd_exit2(t_data *data, char **line)
{
	int	i;

	i = 0;
	while (line[1][i])
	{
		if ((i != 0 || ((line[1][i] != '-' && line[1][i] != '+') && i == 0))
				&& !ft_isdigit(line[1][i]))
		{
			ft_putendl_fd(" : invalid arguments", 2);
			data->exit_status = 255;
			return ;
		}
		i++;
	}
}

void	ms_cmd_exit(t_data *data, char **line)
{
	ft_putstr_fd("exit", 2);
	if (line[1] == NULL)
	{
		data->exit = 1;
		return ;
	}
	else if (!line[2])
	{
		data->exit_status = ft_atoi(line[1]) % 256;
		data->exit = 1;
	}
	else
	{
		ft_putendl_fd(": too many arguments", 2);
		return ;
	}
	ms_cmd_exit2(data, line);
	data->exit = 1;
	return ;
}
