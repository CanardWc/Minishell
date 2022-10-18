#include <minishell.h>

static int	ms_count_limit(char *line)
{
	int	i;

	i = 0;
	if (line[i + 1] == line[i])
		i++;
	while (line[++i] == ' ')
		;
	while (line[i] && !ft_strchr("<> ", line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
			i = (ft_strchr(line + i + 1, line[i]) - line) + 1;
		else
			i++;
	}
	return (i);
}

static int	ms_del_redir(char **line)
{
	char	*tmp;
	char	*ret;
	int	len;

	tmp = *line;
	ret = *line;
	while (*tmp && !ft_strchr("<>", *tmp))
	{
		if (ft_strchr("\"\'", *tmp))
			tmp = ft_strchr(tmp + 1, *tmp) + 1;
		else
			tmp++;
	}
	len = ms_count_limit(tmp);
	*line = ft_strtrim(ft_subsubstr(ret, tmp - ret, len), " ");
	if (!*line)
		return (-1);
	free(ret);
	return (0);
}

static int	ms_exist(char **line)
{
	char	*indic;

	while (**line)
	{
		if (ft_strchr("\'\"", **line))
			*line = ft_strchr(*line + 1, **line);
		if (ft_strchr("<>", **line))
		{
			indic = *line;
			if (*(*line + 1) == **line)
				(*line)++;
			while (*++(*line) == ' ')
				;
			if (!**line || ft_strchr("<>", **line))
			{
				ft_printf("syntax error near unexpected token '%c'\n", **line);
				return (-1);
			}
			*line = indic;
			return (0);
		}
		(*line)++;
	}
	return (0);
}

char	*ms_redirections(char *line, t_token *token)
{
	char	*tmp;

	tmp = line;
	if (ms_exist(&tmp))
		return (NULL);
	if (!*tmp)
		return (line);
	if (ft_strchr("<", *tmp))
		if (ms_in(tmp, token))
			return (NULL);
	if (ft_strchr(">", *tmp))
		if (ms_out(tmp, token))
			return (NULL);
	if (ms_del_redir(&line))
		return (NULL);
	return (ms_redirections(line, token));
}
