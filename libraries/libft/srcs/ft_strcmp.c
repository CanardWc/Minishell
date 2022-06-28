#include <libft.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (0 - (int)*s2);
	if (!s2)
		return ((int)*s1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((int)s1[i] - (int)s2[i]);
}
