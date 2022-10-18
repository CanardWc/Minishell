#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <signal.h>
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

typedef struct	s_token
{
	char	**cmds;

	int	red_in;
	int	red_out;
}	t_token;

typedef struct	s_data
{
	t_list	*tokens;
	t_list	*env;
	t_list	*var;

	char	**true_env;

	int	pipe_count;
	int	std_in;
	int	std_out;
	int	exit_status;
	int	exit;

	char	**to_supr;
	int	ac;
}	t_data;

typedef struct	s_cmds
{
	char	*string;
	void	(*fct)(t_data *, char **);
}	t_cmds;

/*
 *  Utility Functions
 */

void	ms_error(void);
t_list	*ms_build_env(char **env);
void	ms_clear_node(void *);
void	ms_free_nodes(t_data *data);
char	*ft_subsubstr(char *s, int start, int len);

/*
 *  Parsing Functions
 */

void	ms_parsing(t_data *data);
char	**ms_pipes(t_data *data, char *line);
char	*ms_redirections(char *line, t_token *token);
int	ms_in(char *line, t_token *token);
int	ms_out(char *line, t_token *token);
char	**ms_replace_variables(t_data *data, char **cmds);
void	ms_add_variables(t_data *data, t_token *token);
void	ms_flush_variables(t_token *token);
char	**ms_split(const char *s);
int	ms_remove_quotes(char **cmds);

/*
 *  Logic Functions
 */

void	ms_logic(t_data *data);
void	ms_find_cmd(t_data *data, t_token *token);

/*
 *  Builtins Functions
 */

void	ms_cmd_echo(t_data *data, char **line);
void	ms_cmd_cd(t_data *data, char **line);
void	ms_cmd_pwd(t_data *data, char **line);
void	ms_cmd_export(t_data *data, char **line);
void	ms_cmd_unset(t_data *data, char **line);
void	ms_cmd_env(t_data *data, char **line);
void	ms_cmd_exit(t_data *data, char **line);
void	ms_cmd_exec(t_data *data, char **line);

#endif
