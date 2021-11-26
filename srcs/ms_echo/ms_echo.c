//#include <minishell.h>
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int	option;

	if (ac < 2)
	{
		printf("\n");
		return (0);
	}

	option = 0;
	if (!strncmp(av[1], "-n", 2))
		option = 1;
	printf("option = %d\n", option);

	//a suprimer une fois le buitltin associé
	av++;
	if (option)
		av++;

	while (*av)
	{
		printf("%s", *av++);
		if (*av)
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}
