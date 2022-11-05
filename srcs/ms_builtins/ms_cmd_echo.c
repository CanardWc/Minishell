/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:48:18 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:29:02 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ms_check_tnl(char **line)
{
	int	i;
	int	j;

	i = 0;
	while (*line && **line == '-')
	{
		j = 1;
		while ((*line)[j] && (*line)[j] == 'n')
			j++;
		if ((*line)[j] == '\0')
			i++;
		else
			break ;
		line++;
	}
	return (i);
}

void	ms_cmd_echo(t_data *data, char **line)
{
	int	tnl;

	line++;
	tnl = ms_check_tnl(line);
	line += tnl;
	if (!*line || !**line)
		printf("\n");
	else
	{
		while (*line)
		{
			if (*(line + 1))
				printf("%s ", *line++);
			else
				printf("%s", *line++);
		}
		if (!tnl)
			printf("\n");
	}
	data->exit_status = 0;
}
