/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:15:52 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:20:03 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_parse_error(t_data *data, int indic, void *to_free)
{
	to_free = 0;
	data = 0;
	(void)indic;
}

static void	ms_treat_piped(t_data *data, char **piped)
{
	t_token	*token;
	t_list	*node;

	while (*piped)
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->red_in = -2;
		token->red_out = -2;
		*piped = ms_redirections(*piped, token);
		if (!*piped)
			return (ms_parse_error(data, 0, token));
		token->cmds = ms_split(*piped++);
		if (!token->cmds)
			return (ms_parse_error(data, 0, token));
		token->cmds = ms_replace_variables(data, token->cmds);
		if (!token->cmds)
			return (ms_parse_error(data, 0, token));
		ms_add_variables(data, token);
		if (ms_remove_quotes(token->cmds))
			return (ms_parse_error(data, 0, token));
		node = ft_lstnew(token);
		if (!node)
			return (ms_parse_error(data, 0, NULL));
		ft_lstadd_back(&data->tokens, node);
	}
}

int	ms_parsing(t_data *data)
{
	char	*line;
	char	**piped;
	char	**tmp;

	piped = NULL;
	g_position_handler = READLINE;
	line = readline("minishell > ");
	if (g_position_handler == SIGNAL_ALARM)
		errno = 1;
	if (!line)
		return (printf("exit\n") * 0 + 1);
	g_position_handler = MAIN;
	add_history(line);
	if (*line)
		piped = ms_pipes(data, line);
	free(line);
	if (!piped)
		return (0);
	ms_treat_piped(data, piped);
	tmp = piped;
	while (*tmp)
		free(*tmp++);
	free(piped);
	return (0);
}
