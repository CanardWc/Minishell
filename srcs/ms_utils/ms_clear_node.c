/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clear_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:21:34 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:21:37 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_clear_node(void *content)
{
	t_token	*token;
	char	**tmp;

	token = (t_token *)content;
	tmp = (char **)(token->cmds);
	while (*tmp)
	{
		free(*tmp);
		*tmp++ = NULL;
	}
	if (token->red_in > 0)
		close(token->red_in);
	if (token->red_out > 0)
	{
		close(token->red_out);
		remove(".heredoc");
	}
	free(content);
	content = NULL;
}
