/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:15:31 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:29:02 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ms_heredoc(char *file)
{
	char	*line;
	int		fd;

	line = NULL;
	g_position_handler = READLINE;
	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (ft_strcmp(file, line))
	{
		if (line)
			free(line);
		line = readline(">");
		if (ft_strcmp(file, line))
			ft_putendl_fd(line, fd);
		if (!line)
			break ;
	}
	free(line);
	line = NULL;
	close(fd);
	fd = open("/tmp/.heredoc", O_CREAT | O_RDONLY, 0644);
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
		printf("ms_error : %s\n", strerror(errno));
		return (-1);
	}
	if (!indic)
		token->red_in = open(file, O_RDONLY);
	else
		token->red_in = ms_heredoc(file);
	if (token->red_in == -1)
	{
		printf("ms_error: %s: %s\n", file, strerror(errno));
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
	int		indic;
	int		len;

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
