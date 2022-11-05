/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_replace_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:20:54 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:20:59 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ms_free_cmds(char **cmds)
{
	while (*cmds)
		free(*cmds++);
	free(cmds);
	return (NULL);
}

static char	*ms_find_value(t_data *data, char *line, int len)
{
	t_list	*tmp;

	if (len == 0)
		return (NULL);
	if (!ft_strcmp("?", line))
		return (ft_itoa(data->exit_status));
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)(tmp->content))->key, line, len))
			return (((t_env *)(tmp->content))->value);
		tmp = tmp->next;
	}
	tmp = data->var;
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)(tmp->content))->key, line, len))
			return (((t_env *)(tmp->content))->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ms_refresh_line(t_data *data, char **line, int start)
{
	int		len;
	char	*value;
	char	*ret;
	char	*tmp;

	len = 0;
	while ((*line)[start + 1 + len] && \
			!ft_strchr("\'\" ", (*line)[start + 1 + len]))
		len++;
	value = ms_find_value(data, *line + start + 1, len);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(*line) - (len + 1) + \
				ft_strlen(value) + 1));
	if (!ret)
		return (1);
	tmp = ret;
	tmp = ft_memcpy(tmp, *line, start);
	tmp += start;
	tmp = ft_memcpy(tmp, value, ft_strlen(value));
	tmp += ft_strlen(value);
	tmp = ft_memcpy(tmp, *line + start + 1 + len, \
			ft_strlen(*line + start + 1 + len));
	*(tmp + ft_strlen(*line + start + 1 + len)) = '\0';
	free(*line);
	*line = ret;
	return (0);
}

static int	ms_find_variable(char *src)
{
	int	pin;
	int	qts;

	pin = 0;
	qts = 0;
	while (src[pin])
	{
		if (src[pin] == '$')
			if (src[pin + 1] && !(src[pin + 1] == '\"' && qts))
				if (src[pin + 1] != ' ' && src[pin + 1] != '\t')
					return (pin);
		if (src[pin] == '\"' && !qts)
			qts = 1;
		else if (src[pin] == '\"' && qts)
			qts = 0;
		if (src[pin] == '\'')
			while (src[++pin] != '\'')
				;
		pin++;
	}
	return (-1);
}

char	**ms_replace_variables(t_data *data, char **cmds)
{
	char	**tmp;
	int		pin;

	pin = -1;
	tmp = cmds;
	while (*tmp)
	{
		pin = ms_find_variable(*tmp);
		if (pin >= 0)
		{
			if (ms_refresh_line(data, tmp, pin))
				return (ms_free_cmds(cmds));
		}
		else
			tmp++;
	}
	return (cmds);
}
