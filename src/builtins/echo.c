#include "minishell.h"

int	ft_check_n(char **cmd_args)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 1;
	count = 0;
	while (cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
	{
		if (cmd_args[i][0] == '-')
		{
			j = 1;
			while (cmd_args[i][j] == 'n')
				j++;
			if (ft_strlen(cmd_args[i]) == j)
				count++;
			else
				return (count);
		}
		i++;
	}
	return (count);
}

void	ft_echo(char **cmd_args, t_shell *sh)
{
	int	i;

	i = 1;
	if (!cmd_args)
	{
		sh->exit_status = ERROR;
		return ;
	}
	if (!cmd_args[1])
	{
		printf("\n");
		sh->exit_status = SUCCESS;
		return ;
	}
	if (cmd_args[1][0] == '-' && cmd_args[1][1] == 'n')
		i += ft_check_n(cmd_args);
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i++]);
		if (cmd_args[i])
			printf(" ");
	}
	if (ft_strncmp("-n", cmd_args[1], 2) != 0)
		printf("\n");
	sh->exit_status = SUCCESS;
}
