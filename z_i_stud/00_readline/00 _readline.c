// #include "study.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;

	str = NULL;
	str = readline("please insert text:\n");
	printf("your inserted text is: \n%s\n", str);
	free(str);

}

// needs -lreadline in compilation
// in execution with valgrind, use
// valgrind --suppressions=s.supp ./a.out
