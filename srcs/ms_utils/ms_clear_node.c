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
