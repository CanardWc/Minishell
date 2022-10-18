#include <minishell.h>

/*
 *  ms_pipe_error will signal the user for any syntax or 
 *  	malloc failed errors;
 */

static char	**ms_pipe_error(int indic, char c, char **to_free)
{
	char	**tmp;

	tmp = to_free;
	if (indic == 0)
		printf("syntax error near unexpected token '%c'\n", c);
	else
	{
		printf("ms_error : %s\n", strerror(errno));
		while (*tmp)
			free(*tmp++);
		free(to_free);
	}
	return (NULL);
}

/*
 *  ms_fill_ret will fill the array with all the parts of line
 *  	which are separated by a '|';
 */

static char	**ms_fill_ret(char **ret, char *line)
{
	char	**tmp_arr;
	char	*tmp_line;
	
	tmp_arr = ret;
	tmp_line = line;
	while (*tmp_line)
	{
		if (strchr("\'\"", *tmp_line))
			tmp_line = strchr(tmp_line + 1, *tmp_line);
		if (*tmp_line == '|')
		{
			*tmp_arr++ = ft_strtrim( \
				ft_substr(line, 0, tmp_line - line), " ");
			if (!*(tmp_arr - 1))
				return (ms_pipe_error(1, 0, ret));
			while (*++tmp_line == ' ')
				;
			line = tmp_line;
		}
		else
			tmp_line++;
	}
	*tmp_arr++ = strdup(line);
	*tmp_arr = NULL;
	return (ret);
}

/*
 *  ms_count_pipes count the number of '|' and check for any 
 *  	syntax errors related;
 */

static int	ms_count_pipes(char *line)
{
	char	*tmp;
	int	pipe_count;

	pipe_count = 0;
	tmp = line;
	while (*line)
	{
		if (strchr("\'\"", *line))
			line = strchr(line + 1, *line);
		if (!line)
			return (-2);
		if (*line == '|')
		{
			if (line == tmp)
				return (-1);
			pipe_count++;
			while (*++line == ' ')
				;
			if (!*line || *line == '|')
				return (-1);
		}
		else
			line++;
	}
	return (pipe_count);
}

/*
 *  ms_quotes check if all the quotes are respected;
 */

static char	ms_quotes(char *line)
{
	char	*tmp;

	while (*line)
	{
		if (ft_strchr("\'\"", *line))
		{
			tmp = line;
			if (!ft_strchr(tmp, *line))
				return (*line);
			else
				line = ft_strchr(tmp, *line);
		}
		line++;
	}
	return (0);
}

/*
 *  ms_pipes transform the line in an array of all the parts
 * 	separated by a '|'. If there's any error, it will return
 * 	NULL;
 */

char		**ms_pipes(t_data *data, char *line)
{
	char	**ret;
	char	*tmp;

	tmp = line;
	if (ms_quotes(line))
		return (ms_pipe_error(0, ms_quotes(line), NULL));
	data->pipe_count = ms_count_pipes(line);
	if (data->pipe_count == -1)
		return (ms_pipe_error(0, '|', NULL));
	if (data->pipe_count == -2)
		return (ms_pipe_error(0, '\'', NULL));
	ret = (char **)malloc(sizeof(char *) * (data->pipe_count + 2));
	if (!ret)
		return (NULL);
	ret = ms_fill_ret(ret, line);
	if (!ret)
	{
		printf("ms_error : %s\n", strerror(errno));
		return (NULL);
	}
	return (ret);
}
