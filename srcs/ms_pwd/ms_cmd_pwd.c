#include <minishell.h>

void	ms_cmd_pwd(t_data *data, char **line)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		ft_printf("%s\n", cwd);
	else
		ms_error();
	data = 0;
	line = 0;
}
