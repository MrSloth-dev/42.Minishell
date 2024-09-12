#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		int	id;
		char *args[] = {av[2], av[3], av[4]};
	
		id = fork();

		if (id == 0)
		{
			printf("doing execve on child process\n");
			if (execve(av[1], args, NULL) == -1)
				perror("failed");
		}
		else
		{
			wait(NULL);
			printf("\ndoing parent process\n\n");
		}
	}
	else
		printf("need arguments!\n");
	return (0);
}
