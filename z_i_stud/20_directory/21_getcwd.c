#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	char	*buffer;
	char	*cwd;

	buffer = calloc(sizeof(char), 60);
	if (!buffer)
		return (1);

	cwd = getcwd(buffer, 60);

	printf("currrent directory:\n%s\n", cwd);
	
	free (cwd);
	
	return (0);
}
