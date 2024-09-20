#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	if (argc < 2)
		return (1);
	(void)envp;
	printf("Hello, %s", argv[1]);
	ft_readline();
}
