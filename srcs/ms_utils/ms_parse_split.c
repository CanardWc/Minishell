#include <minishell.h>

static char	**ft_arr_size(const char *s)
{
	size_t	l;

	l = 0;
	while (s && *s)
	{
		if (*s != ' ')
			l++;
		if (*s == '\'' || *s == '\"')
			s = ft_memchr(s + 1, *s, ft_strlen(s + 1));
		else if (*s != ' ')
			s = ft_memchr(s + 1, ' ', ft_strlen(s + 1));
		if (s && *s)
			s++;
	}
	return ((char **)ft_calloc(l + 1, sizeof(char *)));
}

void	ms_parse_split(char *s, char ***ret)
{
	char	**arr;
	char	*i;

	*ret = ft_arr_size(s);
	arr = *ret;
	while (s && *s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s && *s != ' ')
		{
			if (*s == '\'' || *s ==  '\"')
				i = ft_memchr(s + 1, *s, ft_strlen(s + 1));
			else
				i = ft_memchr(s + 1, ' ', ft_strlen(s + 1));
			if (i)
				*arr++ = ft_substr(s, 0, i - s + 1);
			else
				*arr++ = ft_substr(s, 0, ft_strlen(s));
		}
		if (i)
			s = i + 1;
		else
			s = i;
	}
}
