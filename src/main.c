#include "minishell.h"

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	printf("Hello, %s", argv[1]);
	ft_readline();
}
