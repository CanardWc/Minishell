#include <minishell.h>

char	*ft_subsubstr(char *s, int start, int len)
{
	char	*ret;
	char	*tmp;
	int	i;

	if (!s || !*s)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) - (len - 1)));
	if (!ret)
		return (NULL);
	tmp = ret;
	i = 0;
	while (s[i])
	{
		if (i == start)
		{
			len += i;
			while (s[i] && i < len)
				i++;
		}
		if (s[i])
			*tmp++ = s[i++];
	}
	*tmp = '\0';
	return (ret);
}
