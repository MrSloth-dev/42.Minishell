#include "../includes/libft.h"
#include "minishell.h"
#include <stdio.h>

void	ft_echo(char **cmd_args, t_shell *sh)
{
	while(cmd_args[i])
	{

		printf("%s ", cmd_args[i]);
	if (ft_strncmp("-n", cmd_args[1], 2) != 0)
		printf("\n");
	sh->error = 1;
	}
}
