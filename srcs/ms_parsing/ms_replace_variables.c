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

	ft_printf("line = [%s], len = [%d]\n", line, len);
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
	int	len;
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

char		**ms_replace_variables(t_data *data, char **cmds)
{
	char	**tmp;
	int	i;

	tmp = cmds;
	while (*tmp)
	{
		i = 0;
		while ((*tmp)[i])
		{
			if ((*tmp)[i] == '\'')
			{
				while ((*tmp)[++i] != '\'')
					;
				i++;
			}
			if ((*tmp)[i] && (*tmp)[i] == '$')
				if (ms_refresh_line(data, tmp, i))
					return (ms_free_cmds(cmds));
			i++;
		}
		tmp++;
	}
	return (cmds);
}
