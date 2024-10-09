#include "minishell.h"

int	ft_check_n(t_token *cmdargs)
{
	size_t	j;
	int		count;

	count = 0;
	while (cmdargs->content[0] == '-' && cmdargs->content[1] == 'n')
	{
		if (cmdargs->content[0] == '-')
		{
			j = 1;
			while (cmdargs->content[j] == 'n')
				j++;
			if (ft_strlen(cmdargs->content) == j)
				count++;
			else
				return (count);
		}
		if (cmdargs->next)
			cmdargs = cmdargs->next;
		else
			break ;
	}
	return (count);
}

void	ft_echo(t_token *cmdargs, t_shell *sh)
{
	t_token	*head;
	int		skip;

	skip = 0;
	head = cmdargs;
	if (!cmdargs->content)
	{
		sh->exit_status = ERROR;
		return ;
	}
	if (!cmdargs->next)
	{
		printf("\n");
		sh->exit_status = SUCCESS;
		return ;
	}
	if (cmdargs->next->content[0] == '-' && cmdargs->next->content[1] == 'n')
		skip += ft_check_n(cmdargs->next);
	while (skip--)
		cmdargs = cmdargs->next;
	while (cmdargs->next)
	{
		printf("%s", cmdargs->next->content);
		if (cmdargs->content)
			printf(" ");
		cmdargs = cmdargs->next;
	}
	if (ft_strcmp("-n", head->next->content) != 0)
		printf("\n");
	sh->exit_status = SUCCESS;
}
