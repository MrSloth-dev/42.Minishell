#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int	main(int ac, char **av)
{
	struct stat	flst;

	if (ac == 2)
	{
		if (stat(av[1], &flst) == -1)
		{
			perror("stat");
			return (1);
		}
		printf ("File: %s\n", av[1]);

		printf ("Size %ld bytes\n", flst.st_size);
		
		printf("Permissions: ");
		if (flst.st_mode & S_IRUSR)
			printf("r");
		else
			printf("-");

		if (flst.st_mode & S_IWUSR)
			printf("w");
		else
			printf("-");

		if (flst.st_mode & S_IXUSR)
			printf("x");
		else
			printf("-");
	
		printf("\n");
		//printf("\nLast modified: %s", ct


	}
	else
		printf("need arguent!\n");

}
