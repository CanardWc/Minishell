/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:58:04 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:20:46 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ms_recreate_line(char **line, int l)
{
	char	*ret;
	char	*str;
	char	*tmp;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(*line) - (l - 1)));
	if (!ret)
		return (1);
	str = ret;
	tmp = *line;
	while (*tmp)
	{
		if (ft_strchr("\'\"", *tmp))
			tmp++;
		else
			*str++ = *tmp++;
	}
	*str = 0;
	free(*line);
	*line = ret;
	return (0);
}

int	ms_remove_quotes(char **cmds)
{
	char	**tmp;
	int		i;
	int		l;

	tmp = cmds;
	while (*tmp)
	{
		i = 0;
		l = 0;
		while ((*tmp)[i])
		{
			if (ft_strchr("\'\"", (*tmp)[i]))
				l++;
			i++;
		}
		if (l)
			if (ms_recreate_line(tmp, l))
				return (1);
		tmp++;
	}
	return (0);
}
