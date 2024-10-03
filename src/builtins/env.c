#include "minishell.h"
#include <unistd.h>

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		ft_printf(STDOUT_FILENO,"%s\n", shell->envp[i++]);
}
