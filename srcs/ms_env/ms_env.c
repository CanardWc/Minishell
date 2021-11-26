//#include <minishell.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	while (*(env + 1))
		printf("%s\n", *env++);
	printf("_=/usr/bin/env\n");
	return (0);
}
