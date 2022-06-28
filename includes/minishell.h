#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

typedef struct	s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct	s_data
{
	t_list	*args;
	t_list	*env;
	t_list	*var;

	char	**true_env;

	int	exit;
}	t_data;

typedef struct	s_cmds
{
	char	*string;
	void	(*fct)(t_data *, char **);
}	t_cmds;

void	ms_error(void);
t_list	*ms_build_env(char **env);
void	ms_clear_node(void *);
void	ms_free_nodes(t_data *data);
void	ms_parse_split(char *s, char ***ret);

void	ms_parse(t_data *data);
void	ms_add_variable(t_data *data);
int	ms_treat_line(t_data *data);
void	ms_exec_line(t_data *data);

void	ms_cmd_echo(t_data *data, char **line);
void	ms_cmd_cd(t_data *data, char **line);
void	ms_cmd_pwd(t_data *data, char **line);
void	ms_cmd_export(t_data *data, char **line);
void	ms_cmd_unset(t_data *data, char **line);
void	ms_cmd_env(t_data *data, char **line);
void	ms_cmd_exit(t_data *data, char **line);
void	ms_cmd_exec(t_data *data, char **line);

#endif
