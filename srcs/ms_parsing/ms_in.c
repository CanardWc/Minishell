#include <minishell.h>

static int	ms_heredoc(char *file)
{
	char	*line;
	int	fd;

	line = NULL;
	fd = open(".heredoc", O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1)
		return (-1);
	while (ft_strcmp(file, line))
	{
		ft_printf(">");
		if (get_next_line(0, &line) < 0)
			return (-1);
		if (ft_strcmp(file, line))
			ft_putstr_fd(line, fd);
	}
	return (fd);
}

static int	ms_set_redir(char *s, int len, int indic, t_token *token)
{
	char	*file;

	if (token->red_in != -2)
		close(token->red_in);
	file = ft_substr(s, 0, len);
	if (!file)
	{
		ft_printf("ms_error : %s\n", strerror(errno));
		return (-1);
	}
	if (!indic)
		token->red_in = open(file, O_RDONLY);
	else
		token->red_in = ms_heredoc(file);
	if (token->red_in == -1)
	{
		ft_printf("ms_error: %s: %s\n", file, strerror(errno));
		free(file);
		return (-1);
	}
	free(file);
	return (0);
}

/*
 * ms_out will indicate if the input redirection is from a file ('<')
 * 	or using heredoc ("<<");
 */

int	ms_in(char *line, t_token *token)
{
	char	*tmp;
	int	indic;
	int	len;

	indic = 0;
	len = 0;
	tmp = line;
	if (*(tmp + 1) == *tmp)
	{
		indic = 1;
		tmp++;
	}
	while (*++tmp == ' ')
		;
	while (tmp[len] && !ft_strchr("<> ", tmp[len]))
	{
		if (ft_strchr("\'\"", *tmp))
			len = (ft_strchr(tmp + len + 1, tmp[len]) - tmp) + 1;
		else
			len++;
	}
	if (ms_set_redir(tmp, len, indic, token))
		return (1);
	return (0);
}
