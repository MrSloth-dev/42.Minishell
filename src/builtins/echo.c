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

int	ft_echo(t_token *cmdargs, t_shell *sh)
{
	t_token	*head;
	t_token	*current;
	int		skip;

	skip = 0;
	head = cmdargs;
	current = head;
	if (!current || !current->content)
		return (ft_printf(STDOUT_FILENO, "\n"), sh->exit_status = EXIT_SUCCESS);
	if (current->content[0] == '-' && current->content[1] == 'n')
		skip += ft_check_n(current);
	while (skip--)
		current = current->next;
	while (current)
	{
		ft_printf(STDOUT_FILENO, "%s", current->content);
		if (current->next != NULL)
			ft_printf(STDOUT_FILENO, " ");
		current = current->next;
	}
	if (ft_strncmp("-n", head->content, 2) != 0)
		ft_printf(STDOUT_FILENO, "\n");
	return (sh->exit_status = EXIT_SUCCESS, 0);
}
