#include <minishell.h>

static int	ms_count_args(char *line)
{
	int	args_count;
	char	indic;

	args_count = 0;
	while (line && *line)
	{
		if (*line == '\"' || *line == '\'')
			indic = *line;
		else if (*line != ' ')
			indic = ' ';
		if (*line != ' ')
		{
			line++;
			if (indic == '\"' || indic == '\'')
				if (!ft_memchr(line, indic, ft_strlen(line)))
				return (0);
			line = ft_memchr(line, indic, ft_strlen(line));
			args_count++;
		}
		if (line && *line)
			line++;		
	}
	return (args_count);
}

static char	*ms_fill_arg_line(char *line, char c)
{
	char	*eoc;
	char	*ret;

	eoc = ft_memchr(line + 1, c, ft_strlen(line));
	ret = ft_substr(line, 0, (eoc - line));
	if (!ret)
		ms_error();
	return (ret);
}

static void	ms_fill_args(t_data *data, char *line, int args_count)
{
	int	i;
	char	indic;

	i = 0;
	while (line && *line && i < args_count)
	{
		if (*line == '\"')
			indic = *line;
		else if (*line == '\'')
			indic = *line;
		else if (*line != ' ')
			indic = ' ';
		if (*line != ' ')
		{
			data->args[i] = ms_fill_arg_line(line, indic);
			line++;
			line = ft_memchr(line, indic, ft_strlen(line));
			i++;
		}
		if (line && *line)
			line++;
	}
	data->args[i] = NULL;
}

void	ms_parse(t_data *data)
{
	int	ret;
	int	args_count;
	char	*line;

	ret = 0;
	if (get_next_line(0, &line) < 0)
		ms_error();
	args_count = ms_count_args(line);
	ft_printf("args_count = %d\n", args_count);
	if (args_count != 0)
	{
		data->args = (char **)malloc(sizeof(char *) * (args_count + 1));
		if (!data->args)
			ms_error();
		ms_fill_args(data, line, args_count);
	}
	free(line);
}
