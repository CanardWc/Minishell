#include <minishell.h>

/*
 * ms_set_redir will open the correct file and add it to the token struct;
 */

static int	ms_set_redir(char *s, int len, int indic, t_token *token)
{
	char	*file;

	if (token->red_out != -2)
		close(token->red_out);
	file = ft_substr(s, 0, len);
	if (!file)
	{
		ft_printf("ms_error : %s\n", strerror(errno));
		return (-1);
	}
	if (!indic)
		token->red_out = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	else
		token->red_out = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	free(file);
	if (token->red_out == -1)
	{
		ft_printf("ms_error : %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

/*
 * ms_out will indicate if the out redirection is a truncated one ('>')
 * 	or a append one (">>");
 */

int	ms_out(char *line, t_token *token)
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
		if (ft_strchr("\'\"", tmp[len]))
			len = (ft_strchr(tmp + len + 1, tmp[len]) - tmp) + 1;
		else
			len++;
	}
	if (ms_set_redir(tmp, len, indic, token))
		return (1);
	return (0);
}
