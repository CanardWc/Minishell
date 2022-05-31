#include <minishell.h>

static char	**ft_arr_size(const char *s)
{
	size_t	l;

	l = 0;
	while (s && *s)
	{
		if (*s != ' ')
			l++;
		while (s && *s && *s != ' ')
		{
			if (*s == '\'' || *s == '\"')
				s = ft_memchr(s + 1, *s, ft_strlen(s + 1));
			s++;
		}
		if (s && *s)
			s++;
	}
	return ((char **)ft_calloc(l + 1, sizeof(char *)));
}

void	ms_parse_split(char *s, char ***ret)
{
	char	**arr;
	char	*i = NULL;

	*ret = ft_arr_size(s);
	arr = *ret;
	while (s && *s)
	{
		while (*s && *s == ' ')
			s++;
		i = s;
		while (i && *i && *i != ' ')
		{
			if (*i == '\'' || *i == '\"')
				i = ft_memchr(i + 1, *i, ft_strlen(i + 1));
			i++;
		}
		*arr++ = ft_substr(s, 0, i - s);
		s = i;
		while (*s && *s == ' ')
			s++;
	}
	*arr = NULL;
}
