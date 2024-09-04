#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int	id;
	int	n;
	int	i;

	id = fork();
	
	if (id == 0)
		n = 1;
	else
		n = 6;

	if (id > 0)
		wait(NULL);

	i = n;
	while (i < (n + 5))
	{
		printf("%d ", i);
		i++;
	}

	if (n == 6)
		printf("\n");
}
