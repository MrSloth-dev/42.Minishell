#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (chdir(av[1]) == 0)
			printf("chdir changed to: %s\n", av[1]);
		else
			printf("chdir: no such file or directory: %s\n", av[1]);
	}
	else
		printf("you need an argument!\n");
}
