#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int ac, char **av)
{
	int		id;
	int		len;
	char	*str;
	int		j;
	int 	res;

	(void)ac;
	if (!av[1] || !av[1][0])
	{
		printf("need argument!\n");
		exit (1);
	}

	id = fork();
	printf("started %d process\n ", id);

	len = 0;
	while (av[1][len] != 0)
		len++;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	bzero((void *)str, len + 1);

	j = -1;
	while(av[1][++j])
		str[j] = av[1][j];

// verify if i'm running child process
	if (id == 0)
	 	sleep (1);

	printf("doing process %d,   id %d,     and str is: %s\n", getpid(), id, str);
	
// certify that i will terminate child process before main process
	res = wait(NULL);
	if (res == -1)
		printf("no child to wait\n");
	else 
		printf("terminating main process");

	free(str);
	return (0);
}
