//#include <minishell.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int	main(int ac, char **av)
{
	if (chdir(av[1]))
		printf("%s\n", strerror(errno));
	return (0);
}
