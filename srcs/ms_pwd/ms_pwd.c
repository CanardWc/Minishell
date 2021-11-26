//#include <minishell.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char	*buf = NULL;

	buf = getcwd(buf, 0);

	//error management;
	if (!buf)
		return (0);

	printf("%s\n", buf);
	free(buf);
	return (0);
}
