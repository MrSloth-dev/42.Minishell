#include "../includes/libft.h"
#include "minishell.h"
#include <stdio.h>

void	ft_echo(char **cmd_args, t_shell *sh)
{
	int	i;

	i = 1;
	if (ft_strncmp("echo", cmd_args[0], 5) != 0 || !cmd_args[1])
	{
		printf("\n");
		sh->exit_status = SUCCESS;
		return ;

	}
	if (ft_strncmp("-n", cmd_args[1], 2) == 0)
		i = 2;
	while(cmd_args[i])
	{
		printf("%s", cmd_args[i++]);
		if (cmd_args[i])
			printf(" ");
	}
	if (ft_strncmp("-n", cmd_args[1], 2) != 0)
		printf("\n");
	sh->exit_status = SUCCESS;
}
