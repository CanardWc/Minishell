#include <minishell.h>

void	ms_free_nodes(t_data *data)
{
	ft_lstclear(&data->args, &ms_clear_node);
}

static void	ms_add_node(t_data *data, char *s)
{
	t_list	*node;
	char	**content;

	if (!s)
		ms_error();
	ms_parse_split(s, &content);
	if (!content)
		ms_error();
	node = ft_lstnew(content);
	if (!node)
		ms_error();
	ft_lstadd_back(&data->args, node);
	free(s);
}

int	ms_check_void(char *s, int i)
{
	int y;

	y = 0;
	while (y < i)
		if (s[y++] != ' ')
			return (1);
	return (0);
}

static void	ms_get_args(t_data *data, char *s)
{
	int	i;
	char	*tmp;

	i = 0;
	if (ft_strchr("<>|", s[i]))
		i += 1 + (ft_strchr("<>", s[i]) && s[i + 1] == s[i]);
	else
	{
		while (s[i] && !ft_strchr("|<>", s[i]))
		{
			if (ft_strchr("\'\"", s[i]))
			{
				tmp = s + i + 1;
				if (!ft_memchr(tmp, s[i], ft_strlen(tmp)))
					return (ms_free_nodes(data));
				i = (char *)ft_memchr(tmp, s[i], \
						ft_strlen(tmp)) - s;
			}
			i++;
		}
	}
	if (ms_check_void(s, i))
		ms_add_node(data, ft_substr(s, 0, i));
	if (*(s + i))
		ms_get_args(data, s + i);
}

void	ms_parse(t_data *data)
{
	char	*line;

	if (get_next_line(0, &line) < 0)
		ms_error();
	if (*line)
		ms_get_args(data, line);
	free(line);
}
