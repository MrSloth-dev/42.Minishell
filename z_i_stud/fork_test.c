#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int	main(void)
{	
	char	*str;

	str = calloc(sizeof(char) * 100, 1);
	
	if (fork() == 0)
	{
		free(str);
		exit(0);
	}
	free(str);







}
