#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int	main(int argc, char *argv[])
{
	struct stat path_stat;
	if (argc != 2)
		return 0;
	stat(argv[1], &path_stat);
	printf("%d\n", S_ISREG(path_stat.st_mode));
}
