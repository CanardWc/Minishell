#include <libft.h>

unsigned int	check(char *str)
{
	unsigned int	i;

	while (*str)
	{
		i = 1;
		if (*str == '-' || *str == '+')
			return (1);
		while (str[i])
			if (*str == str[i++])
				return (1);
		str++;
	}
	return (0);
}

void			ft_putnbr_base_fd(int nbr, char *base, int fd)
{
	unsigned int	s;
	unsigned int	n;

	if ((s = ft_strlen(base)) < 2 || check(base))
		return ;
	if (nbr < 0)
		write(1, "-", 1);
	n = nbr < 0 ? nbr * -1 : nbr;
	if (n > s - 1)
		ft_putnbr_base_fd(n / s, base, fd);
	write(fd, &base[n % s], 1);
}
