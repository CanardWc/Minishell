#include <libft.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	return ((*s1 && *s2 && *s1 == *s2 && n > 0) ? \
		ft_strncmp(++s1, ++s2, --n) : \
		(unsigned char)(*s1) - (unsigned char)(*s2));
}
