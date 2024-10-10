#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_exit(char *pwd, t_shell *shell)
{
	if (pwd != NULL)
		free(pwd);
	//befpre
	//if (shell->token_lst)
	//free(shell->token_lst)
	//but this entry an invalid free, because have same free when executed one line before (removed that same free of ft_free_tree)
	//free(shell->token_lst);
	if (shell->line)
		free(shell->line);
	if (shell->envp)
		ft_free_envp(shell->envp);
	if (shell->path)
		ft_free_envp(shell->path);
	free(shell);
	ft_printf(STDOUT_FILENO, "exit\n");
	exit (EXIT_SUCCESS);
}
