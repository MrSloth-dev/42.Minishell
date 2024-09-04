#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int ac, char **av)
{
	int	id;
	int	len;
//	int	test;
	char	*str;

	(void)ac;

	id = fork();
	printf("started %d process\n ", id);
	len = 0;
	while (av[1][len] != 0)
		len++;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	bzero((void *)str, len);

	int j = -1;
	while(av[1][++j])
		str[j] = av[1][j];

	if (id > 0)
		sleep (2);

	printf("doing process %d,   id %d,     and str is: %s\n", getpid(), id, str);

	free(str);
	// test = wait(NULL);
	// if (test > 0)
	// 	printf("finishing parent process\n");
	// else
	// 	printf("doing child process\n");
	//



	return (0);
}
