#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct	s_data
{
	t_list	*args;
	char	**env;
	int	exit;
}	t_data;

void	ms_error(void);
void	ms_clear_node(void *);
void	ms_parse_split(char *s, char ***ret);

void	ms_parse(t_data *data);

#endif
