#include <unistd.h>
#include <stdio.h>

int	main()
{
	int	id;
	id = fork();
	if (id > 0)
		fork();
	if (id == 0)
	{
		printf("child process with %d PID\n", id);//this appear second on terminal	
	}	
	else if (id > 0)
	{
		printf("parent process with %d PID\n", id); //this appear first on terminal
	}
	else
		printf("error, PID minor than zero\n");
}
