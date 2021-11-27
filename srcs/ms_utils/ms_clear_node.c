#include <minishell.h>

void	ms_clear_node(void *content)
{
	char	**tmp;
	char	**ret;

	ret = (char **)content;
	tmp = ret;
	while (*tmp)
	{
		free(*tmp);
		*tmp++ = NULL;
	}
	free(ret);
	ret = NULL;
}
