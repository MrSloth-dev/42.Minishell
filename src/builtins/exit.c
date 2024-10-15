#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_free_and_exit(char *pwd, t_shell *shell)
{
	if (shell)
	{
		if (pwd != NULL)
			free(pwd);
		if (shell->line)
			free(shell->line);
		if (shell->token_lst)
		{
			ft_free_tree(shell->token_lst);
			free(shell->token_lst);
		}
		if (shell->envp)
			ft_free_envp(shell->envp);
		if (shell->path)
			ft_free_envp(shell->path);
		free(shell);
	}
	exit (EXIT_SUCCESS);
}

void	ft_exit(char *pwd, t_shell *shell)
{
	ft_printf(STDOUT_FILENO, "exit\n");
	ft_free_and_exit(pwd, shell);
}
