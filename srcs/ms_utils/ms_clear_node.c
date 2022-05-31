#include <minishell.h>

void	ms_clear_node(void *content)
{
	char	**tmp;

	tmp = (char **)content;
	while (*tmp)
	{
		free(*tmp);
		*tmp++ = NULL;
	}
	free(content);
	content = NULL;
}
