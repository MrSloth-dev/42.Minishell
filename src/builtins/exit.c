#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_exit(char *pwd, t_shell *shell)
{
	if (pwd != NULL)
		free(pwd);
	if (shell->token_lst)
		ft_free_tree(shell->token_lst);
	if (shell->line)
		free(shell->line);
	if (shell->envp)
		ft_free_envp(shell->envp);
	free(shell);
	ft_printf(STDOUT_FILENO, "exit\n");
	exit (EXIT_SUCCESS);
}
