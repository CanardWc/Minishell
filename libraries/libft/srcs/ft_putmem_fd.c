#include <libft.h>

void	ft_putmem_fd(unsigned long int pt_addr, int fd)
{
	if (pt_addr > 15)
		ft_putmem_fd(pt_addr >> 4, fd);
	ft_putnbr_base_fd(pt_addr % 16, "0123456789abcdef", fd);
}
